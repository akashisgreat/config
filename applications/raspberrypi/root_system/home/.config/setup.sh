sudo apt update -y
sudo apt install zsh neovim tmux libsndfile1-dev git fzf bat python tree ffmpeg ranger -y 

sleep .5;
ln -s ~/.config/shell/zshrc ~/.zshrc
sleep .5;
echo -e "\nChanging shell to zsh (required passwd)"
sleep 2;
chsh -s $(which zsh)
echo "Shell changed to zsh sucessfully."
