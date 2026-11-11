"""Regressions for parameter ownership and private-data exclusion in log exports."""
import json
import tempfile
import unittest
from pathlib import Path

from inspect_cluster_navigation_flow import inspect_log


class LogExportTest(unittest.TestCase):
    def inspect(self, *bodies):
        lines = ['Version: 20028 (20028) release']
        lines.extend(f'2026-11-11T05:44:20.000000Z [549f0b99] {body}' for body in bodies)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'device.log'
            path.write_text('\n'.join(lines), encoding='utf-8')
            return inspect_log(path)

    def test_parameter_ids_survive_reordered_fields_and_private_values_are_excluded(self):
        result = self.inspect(
            'debug navigation event=wire direction=tx id=5201 source=runtime tx=76 fields=5',
            'debug navigation event=field direction=tx id=5201 source=runtime tx=76 field=10 index=0 name=distanceToManeuver value=245',
            'debug navigation event=field direction=tx id=5201 source=runtime tx=76 field=13 index=1 name=maneuverIndex value=1',
            'debug navigation event=field direction=tx id=5201 source=runtime tx=76 field=3 index=2 name=currentRoad value=12345',
            'debug navigation event=field direction=tx id=5201 source=runtime tx=76 field=7 index=3 name=private value=67890',
            'debug navigation event=field direction=tx id=5201 source=runtime tx=76 field=4 index=4 name=destination value=private destination',
            'debug navigation event=transport direction=tx id=5201 tx=76 completed=true')
        packet = result['sessions']['549f0b99']['navigation_packets'][0]
        self.assertEqual({'10': 245, '13': 1}, packet['fields'])
        self.assertTrue(packet['transport_completed'])
        exported = json.dumps(result)
        self.assertNotIn('12345', exported)
        self.assertNotIn('67890', exported)
        self.assertNotIn('private destination', exported)

    def test_message_id_isolates_transaction_correlation(self):
        result = self.inspect(
            'debug navigation event=wire direction=tx id=5202 source=runtime tx=75 fields=1',
            'debug navigation event=field direction=tx id=5201 source=runtime tx=75 field=1 index=0 name=guidanceState value=2',
            'debug navigation event=transport direction=tx id=5201 tx=75 completed=true',
            'debug navigation event=field direction=tx id=5202 source=runtime tx=75 field=3 index=0 name=type value=1')
        packet = result['sessions']['549f0b99']['navigation_packets'][0]
        self.assertEqual({'3': 1}, packet['fields'])
        self.assertNotIn('transport_completed', packet)

    def test_only_accepted_runtime_start_is_recorded(self):
        result = self.inspect(
            'debug navigation event=subscription id=5200 accepted=false link=4 subscription=4 components=[42] options=3',
            'debug navigation event=subscription id=5200 accepted=true link=4 subscription=5 components=[42, 99] options=3')
        starts = result['sessions']['549f0b99']['runtime_navigation_starts']
        self.assertEqual(1, len(starts))
        self.assertEqual([42, 99], starts[0]['components'])
        self.assertEqual(5, starts[0]['subscription'])


if __name__ == '__main__':
    unittest.main()
