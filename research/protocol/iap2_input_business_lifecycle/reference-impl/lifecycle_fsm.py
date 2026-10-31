#!/usr/bin/env python3
"""本地安全参考模型，不是 Apple FSM；不执行认证或网络 I/O。
按单个业务域使用，READY 由真实会话/业务层验证后提交。
epoch 是本地回调票据而非线上会话号；调用方须串行投递事件。
"""
from dataclasses import dataclass, field
from itertools import product

ACTIVE = "ACTIVE"
SUSPENDED = "SUSPENDED"
RESUMED = "RESUMED"
DISCONNECTED = "DISCONNECTED"
RECONNECTING = "RECONNECTING"
NEGOTIATING = "NEGOTIATING"

TRANSITIONS = {
    (DISCONNECTED, "RECONNECT"): RECONNECTING,
    (RECONNECTING, "ESTABLISHED"): NEGOTIATING,
    (NEGOTIATING, "READY"): ACTIVE,
    (ACTIVE, "SUSPEND"): SUSPENDED,
    (SUSPENDED, "RESUME"): RESUMED,
    (RESUMED, "READY"): ACTIVE,
    (RESUMED, "SUSPEND"): SUSPENDED,
    (SUSPENDED, "SUSPEND"): SUSPENDED,
    (RECONNECTING, "RECONNECT"): RECONNECTING,
    (DISCONNECTED, "DETACH"): DISCONNECTED,
    (RECONNECTING, "DETACH"): DISCONNECTED,
    (NEGOTIATING, "DETACH"): DISCONNECTED,
    (ACTIVE, "DETACH"): DISCONNECTED,
    (SUSPENDED, "DETACH"): DISCONNECTED,
    (RESUMED, "DETACH"): DISCONNECTED,
    (RECONNECTING, "FAIL"): DISCONNECTED,
    (NEGOTIATING, "FAIL"): DISCONNECTED,
    (ACTIVE, "FAIL"): DISCONNECTED,
    (SUSPENDED, "FAIL"): DISCONNECTED,
    (RESUMED, "FAIL"): DISCONNECTED,
    (RECONNECTING, "CANCEL"): DISCONNECTED,
    (NEGOTIATING, "CANCEL"): DISCONNECTED,
}


@dataclass
class Lifecycle:
    state: str = field(default=DISCONNECTED, init=False)
    epoch: int = field(default=0, init=False)
    _ready: bool = field(default=False, init=False)
    history: list = field(default_factory=list, init=False)

    @property
    def can_send_business(self):
        return self.state == ACTIVE and self._ready

    @property
    def timers_paused(self):
        # Only business timers, NOT link ACK/retransmission/handshake timers.
        return not self.can_send_business

    def can(self, event):
        """只检查迁移边；不代替 epoch/READY 条件验证。"""
        return (self.state, event) in TRANSITIONS

    def apply(self, event, *, epoch, authenticated=False,
              identified=False, feature_ready=False):
        if type(epoch) is not int or epoch != self.epoch:
            raise ValueError("stale or invalid epoch")
        key = (self.state, event)
        if key not in TRANSITIONS:
            raise ValueError(f"illegal transition: {self.state} --{event}-->")
        if event == "READY" and not all(x is True for x in
                                        (authenticated, identified, feature_ready)):
            raise ValueError("READY requires authentication, identification and feature gates")
        new = TRANSITIONS[key]
        if ((event == "RECONNECT" and self.state == DISCONNECTED)
                or (event == "SUSPEND" and self.state != SUSPENDED)
                or (new == DISCONNECTED and self.state != DISCONNECTED)):
            self.epoch += 1
        self._ready = new == ACTIVE
        self.history.append((self.state, event, new))
        self.state = new
        return new


def _self_test():
    def event(lc, name, **kwargs):
        return lc.apply(name, epoch=lc.epoch, **kwargs)

    def rejected(lc, name, **kwargs):
        before = (lc.state, lc.epoch, lc.can_send_business, list(lc.history))
        try:
            lc.apply(name, **kwargs)
        except ValueError:
            assert before == (lc.state, lc.epoch, lc.can_send_business, lc.history)
        else:
            raise AssertionError(f"unexpected acceptance: {name}")

    def reach(state):
        lc = Lifecycle()
        if state == DISCONNECTED:
            return lc
        event(lc, "RECONNECT")
        if state == RECONNECTING:
            return lc
        event(lc, "ESTABLISHED")
        if state == NEGOTIATING:
            return lc
        event(lc, "READY", authenticated=True, identified=True, feature_ready=True)
        if state == ACTIVE:
            return lc
        event(lc, "SUSPEND")
        if state == SUSPENDED:
            return lc
        event(lc, "RESUME")
        assert state == RESUMED
        return lc

    lc = Lifecycle()
    assert lc.state == DISCONNECTED and lc.timers_paused
    rejected(lc, "READY", epoch=lc.epoch, authenticated=True,
             identified=True, feature_ready=True)
    event(lc, "RECONNECT")
    ticket = lc.epoch
    event(lc, "ESTABLISHED")
    assert not lc.can_send_business and lc.timers_paused
    event(lc, "DETACH")
    event(lc, "RECONNECT")
    rejected(lc, "ESTABLISHED", epoch=ticket)
    event(lc, "ESTABLISHED")
    rejected(lc, "READY", epoch=ticket, authenticated=True,
             identified=True, feature_ready=True)

    for state in (NEGOTIATING, RESUMED):
        for a, i, f in product((False, True), repeat=3):
            lc = reach(state)
            assert lc.timers_paused and not lc.can_send_business
            args = dict(epoch=lc.epoch, authenticated=a, identified=i, feature_ready=f)
            if a and i and f:
                lc.apply("READY", **args)
                assert lc.can_send_business and not lc.timers_paused
            else:
                rejected(lc, "READY", **args)

    for (state, name), expected in TRANSITIONS.items():
        lc = reach(state)
        event(lc, name, authenticated=True, identified=True, feature_ready=True)
        assert lc.state == expected
        assert lc.can_send_business == (expected == ACTIVE)
        assert lc.timers_paused == (expected != ACTIVE)

    lc = reach(ACTIVE)
    old = lc.epoch
    event(lc, "SUSPEND")
    event(lc, "RESUME")
    rejected(lc, "READY", epoch=old, authenticated=True,
             identified=True, feature_ready=True)
    rejected(lc, "READY", epoch=lc.epoch, authenticated=1,
             identified=True, feature_ready=True)
    rejected(lc, "ESTABLISHED", epoch=lc.epoch)
    print("lifecycle_fsm: 22 edges, 16 READY combinations, stale/rejected invariants OK")


if __name__ == "__main__":
    _self_test()
