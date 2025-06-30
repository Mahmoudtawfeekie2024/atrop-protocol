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
# Create user for non-root dev
# --------------------------------
RUN useradd -ms /bin/bash atropuser
USER atropuser

# --------------------------------
# Set up workspace
# --------------------------------
WORKDIR /app
COPY . .

# Shared source volumes (for mounting outside)
VOLUME ["/app/daemon", "/app/sdk", "/app/test"]

# --------------------------------
# Default build action (optional)
# --------------------------------
RUN make all

# --------------------------------
# Boot into interactive shell (or override via CMD)
# --------------------------------
CMD ["/bin/bash"]
