# ================================
# 🐳 ATROP Protocol Dev Container
# ================================
FROM python:3.10-slim

LABEL maintainer="Mahmoud Tawfeek"
LABEL description="Dockerfile for ATROP protocol build and test system"

ARG DEBIAN_FRONTEND=noninteractive

# --------------------------------
# OS + Build & Developer Essentials
# --------------------------------
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    make \
    git \
    curl \
    htop \
    protobuf-compiler \
    libgtest-dev \
    bash-completion \
    iputils-ping \
    net-tools \
    tcpdump \
    && rm -rf /var/lib/apt/lists/*

# --------------------------------
# Python Dev Requirements
# --------------------------------
COPY dev-requirements.txt /tmp/dev-requirements.txt
RUN pip install --upgrade pip && \
    pip install -r /tmp/dev-requirements.txt && \
    pip install virtualenv

# --------------------------------
# Create non-root user for safe development
# --------------------------------
RUN useradd -ms /bin/bash atropuser
USER atropuser

# --------------------------------
# Add ATROP Developer Shell Aliases
# --------------------------------
RUN echo '\n# === ATROP Dev Aliases ===' >> /home/atropuser/.bashrc && \
    echo "alias ll='ls -alF --color=auto'" >> /home/atropuser/.bashrc && \
    echo "alias gs='git status'" >> /home/atropuser/.bashrc && \
    echo "alias gc='git commit'" >> /home/atropuser/.bashrc && \
    echo "alias ga='git add'" >> /home/atropuser/.bashrc && \
    echo "alias gp='git push'" >> /home/atropuser/.bashrc && \
    echo "alias gco='git checkout'" >> /home/atropuser/.bashrc && \
    echo "alias cdp='cd /app/protocol'" >> /home/atropuser/.bashrc && \
    echo "alias cdcp='cd /app/daemon/control_plane'" >> /home/atropuser/.bashrc && \
    echo "alias cddp='cd /app/daemon/data_plane'" >> /home/atropuser/.bashrc && \
    echo "alias cdtest='cd /app/test'" >> /home/atropuser/.bashrc && \
    echo "alias atest='pytest test/unit/'" >> /home/atropuser/.bashrc && \
    echo "alias rebuild='make clean && make all'" >> /home/atropuser/.bashrc && \
    chown atropuser:atropuser /home/atropuser/.bashrc

# --------------------------------
# Set up workspace
# --------------------------------
WORKDIR /app
COPY . .

# Mount key development areas
VOLUME ["/app/daemon", "/app/sdk", "/app/test"]

# --------------------------------
# Default build (optional for CI/local builds)
# --------------------------------
RUN make all

# --------------------------------
# Default command — attach to shell
# --------------------------------
CMD ["/bin/bash"]
