#!/bin/bash

# Start a new tmux session
SESSION_NAME="turtlebot3_sim"
tmux new-session -d -s $SESSION_NAME

# Split the window into two panes
tmux split-window -h

# Select the first pane and launch Gazebo
tmux select-pane -t 0
tmux send-keys "source ~/.bashrc && export TURTLEBOT3_MODEL=burger && ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py" C-m

# Select the second pane and launch Navigation2
tmux select-pane -t 1
tmux send-keys "source ~/.bashrc && export TURTLEBOT3_MODEL=burger && ros2 launch turtlebot3_navigation2 navigation2.launch.py use_sim_time:=True map:=$HOME/map.yaml" C-m

# Attach to the tmux session
tmux attach-session -t $SESSION_NAME
