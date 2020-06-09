#!/usr/bin/env bash

echo -e "set number\nsyntax on\nset tabstop=2 shiftwidth=2 expandtab\nfiletype plugin indent on\n" >> ~/.vimrc

mkdir ~/.config
mkdir ~/.config/nvim
echo -e "set runtimepath^=~/.vim runtimepath+=~/.vim/after\nlet &packpath=&runtimepath\nsource ~/.vimrc\n" >> ~/.config/nvim/init.vim

