# Basic shell commands

## find
```bash
# Recursively find core files in directory src/ located in the current directory and remove them
find src -name core -exec rm {} \;
```

## chmod
```bash
# Make a.out executable
chmod +x a.out
# Make it not executable
chmod -x a.out
# Make private/ inaccessible
chmod 000 private
# Make it accessible
chmod 755 private
```

## grep
```bash
# Find the string "root" in the file /etc/passwd
grep root /etc/passwd
```

## ps/kill
```bash
# In one terminal windows, create a vim process
vim hello.c
# In another window, terminate it
kill -KILL $(ps -C vim -o pid=)
```

## ln
```bash
# Make a link to hello.c with the name link_to_hello
ln hello.c link_to_hello
```

## apt
```bash
# Install SSH server
sudo apt update && sudo apt upgrade && sudo apt install openssh-server
```

## ssh
```bash
# Connect to STUDENTA SSH server
STUDENTA_HOST_IP=172.217.24.206
USERNAME=user1
ssh "$USERNAME@$STUDENTA_HOST_IP"
```

## wget
```bash
# Download the slide 0-intro.pdf to the current directory
wget https://github.com/hagimont/OS2020/blob/master/0-intro.pdf
```

## tar
```bash
# Uncompress abc archive
tar -xf abc.tar
# Create def archive
tar -cf def
```

## pipe
```bash
# Count number of running firefox processes
ps -ef | grep firefox | wc -l
```
