#!/bin/sh

# Run this before compiling main.c

echo "Creating $HOME/bin if not exists..."
mkdir -p $HOME/bin
echo "Copying \`\`gendoc'' and \`\`Print'' scripts to $HOME/bin..."
cp gendoc Print $HOME/bin