FROM ros:melodic

ARG UID 1000
ARG GID 1000

RUN apt update -y && \
  apt upgrade -y && \
  apt install -y python3-pip

RUN groupadd --gid $GID notroot && \
  useradd --uid $UID --gid $GID --shell /bin/bash --create-home notroot && \
  cp /root/.bashrc /home/notroot && \
  chown $UID:$GID /home/notroot/.bashrc && \
  echo "notroot ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN sed -i "s/#force_color/force_color/" /home/notroot/.bashrc && \
  echo "source /opt/ros/melodic/setup.bash" >> /home/notroot/.bashrc

RUN python3 -m pip install catkin_pkg

