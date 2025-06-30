# ================================
# 🐳 ATROP Protocol Dev Container
# ================================
FROM python:3.10-slim

LABEL maintainer="Mahmoud Tawfeek"
LABEL description="Dockerfile for ATROP protocol build and test system"

# --------------------------------
# OS + Build Essentials
# --------------------------------
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    make \
    git \
    protobuf-compiler \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# --------------------------------
# Python Dev Requirements
# --------------------------------
COPY dev-requirements.txt /tmp/dev-requirements.txt
RUN pip install --upgrade pip && \
    pip install -r /tmp/dev-requirements.txt

# --------------------------------
# Set up workspace
# --------------------------------
WORKDIR /app
COPY . .

# --------------------------------
# Default build action
# --------------------------------
RUN make all

CMD ["/bin/bash"]
