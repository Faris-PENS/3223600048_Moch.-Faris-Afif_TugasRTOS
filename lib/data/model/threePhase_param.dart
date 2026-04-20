class PhaseData {
  final int index;
  final double arus;

  PhaseData(this.index, this.arus);
}

class LoadData {
  final int index;
  final double arus;
  final String? phase;

  LoadData(this.index, this.arus, this.phase);
}

class StateUpdate  {
  final bool? connected;
  final int? mode;
  final bool? isBalanceable;
  final List<PhaseData>? phases;
  final List<LoadData>? loads;
  final String? status;

  StateUpdate ({
    this.connected,
    this.mode,
    this.isBalanceable,
    this.phases,
    this.loads,
    this.status,
  });
}