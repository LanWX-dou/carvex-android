# Project Documentation

This directory contains workspace-level documentation for the `carvex-carplay-research`
repository only.

- `architecture.md`: repository split, layers and ownership boundaries.
- `workflows.md`: common research and development workflows.
- `status.md`: current structure, priorities and repository notes.
- `decisions/`: durable architecture and process decisions.

Current design proposals:

- [Navigation delivery to the vehicle instrument cluster](../openspec/changes/replan-carplay-navigation-cluster/design.md): source events, session snapshots, current-link subscriptions, iAP2 publication and staged implementation. The numeric core is implemented against reviewed Apple and GalaxyPlay evidence; vehicle acceptance remains pending. See the [decision record](decisions/0001-navigation-cluster-chain.md) and [tasks](../openspec/changes/replan-carplay-navigation-cluster/tasks.md).

Normative protocol specifications live under `research/`. The Android and firmware
repositories keep their own README/AGENT files.
