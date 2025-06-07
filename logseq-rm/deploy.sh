#!/usr/bin/env bash
set -e
DEST=/opt/logseq-rm

rsync -av --delete build/out/ root@10.11.99.1:${DEST}/
scp package/logseq-rm.service root@10.11.99.1:/home/root/.

ssh root@10.11.99.1 <<'EOFREMOTE'
mkdir -p ~/.config/systemd/user
mv ~/logseq-rm.service ~/.config/systemd/user/
systemctl --user daemon-reload
systemctl --user enable logseq-rm
systemctl --user restart logseq-rm
EOFREMOTE
