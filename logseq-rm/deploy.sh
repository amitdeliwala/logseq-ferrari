#!/bin/bash
# deploy.sh (run from host)
scp build/logseq-rm root@10.11.99.1:/opt/logseq-rm/
scp build/logseq-cli root@10.11.99.1:/opt/logseq-rm/bin/

ssh root@10.11.99.1 <<'SERVICE'
cat >/home/root/.config/systemd/user/logseq-rm.service <<UNIT
[Unit]
After=xochitl.service
[Service]
ExecStart=/opt/logseq-rm/logseq-rm
Restart=on-failure
Environment=QT_QPA_PLATFORM=epaper
Environment=QT_QUICK_BACKEND=epaper
[Install]
WantedBy=default.target
UNIT
systemctl --user daemon-reload
systemctl --user enable logseq-rm
SERVICE
