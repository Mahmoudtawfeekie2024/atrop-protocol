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
RUN apt-get update && apt-get install -y --no-install-recommends \
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
    pip install --no-cache-dir -r /tmp/dev-requirements.txt && \
    pip install --no-cache-dir virtualenv

# --------------------------------
# Create non-root user for safe development
# --------------------------------
RUN useradd -ms /bin/bash atropuser
USER atropuser

# --------------------------------
# Add ATROP Developer Shell Aliases
# --------------------------------
RUN printf '\n# === ATROP Dev Aliases ===\n' >> /home/atropuser/.bashrc && \
    printf "alias ll='ls -alF --color=auto'\n" >> /home/atropuser/.bashrc && \
    printf "alias gs='git status'\n" >> /home/atropuser/.bashrc && \
    printf "alias gc='git commit'\n" >> /home/atropuser/.bashrc && \
    printf "alias ga='git add'\n" >> /home/atropuser/.bashrc && \
    printf "alias gp='git push'\n" >> /home/atropuser/.bashrc && \
    printf "alias gco='git checkout'\n" >> /home/atropuser/.bashrc && \
    printf "alias cdp='cd /app/protocol'\n" >> /home/atropuser/.bashrc && \
    printf "alias cdcp='cd /app/daemon/control_plane'\n" >> /home/atropuser/.bashrc && \
    printf "alias cddp='cd /app/daemon/data_plane'\n" >> /home/atropuser/.bashrc && \
    printf "alias cdtest='cd /app/test'\n" >> /home/atropuser/.bashrc && \
    printf "alias atest='pytest test/unit/'\n" >> /home/atropuser/.bashrc && \
    printf "alias rebuild='make clean && make all'\n" >> /home/atropuser/.bashrc && \
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
