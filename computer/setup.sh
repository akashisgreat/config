#mkdir -p ~/des
#mkdir -p ~/dl
#mkdir -p ~/doc
#mkdir -p ~/doc/code
#mkdir -p ~/doc/study
#mkdir -p ~/music
#mkdir -p ~/pic
#mkdir -p ~/pic/ss
#mkdir -p ~/pic/wall
#ln -s $HOME/.config/shell/zshrc $HOME/.zshrc
#xargs -a $HOME/.config/computer/apps sudo pacman --noconfirm -S
#
#
echo "Instruction to git backup the config file."
echo "------------------------------------------"
echo "cd .config
xargs -a ~/config/computer/paths git add 
git commit -m 'My commit' 
git push -u origin main"

