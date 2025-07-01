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
    build-essential=12.10ubuntu1 \
    cmake=3.28.3-1build7 \
    g++=4:13.2.0-7ubuntu1 \
    make=4.3-4.1build2 \
    git=1:2.43.0-1ubuntu1 \
    curl=8.5.0-1 \
    htop=3.2.2-1 \
    protobuf-compiler=3.21.12-8.2ubuntu0.1 \
    libgtest-dev=1.14.0-1 \
    bash-completion=1:2.11-7 \
    iputils-ping=3:20221126-1build1 \
    net-tools=1.60+git20181103.0eebece-2ubuntu1 \
    tcpdump=4.99.4-1ubuntu1 \
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
