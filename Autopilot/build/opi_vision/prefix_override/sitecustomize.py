import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/avcpp/AV-CPP2025/Autopilot/install/opi_vision'
