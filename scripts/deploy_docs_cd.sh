#!/bin/bash

# Reset
COLOR_RESET='\033[0m' # Text Reset

# Regular Colors
CYAN='\033[0;36m' # Cyan

# Background
ON_RED='\033[41m'    # Red
ON_GREEN='\033[42m'  # Green
ON_YELLOW='\033[43m' # Yellow

# This script is used to generate the documentation for the
# JIT compiler as well as the repo as a whole. It is used
# by the CI system to generate the documentation for the
# docs website.

# This script is meant to be run from the root of the repo.

DOCKER_IMAGE="pulanski/nginx_hugo:0.0.1"

# Exit on error
set -e

# Log the docker image being built
echo "${ON_YELLOW} INFO ${COLOR_RESET} ${CYAN} Building docker image: ${DOCKER_IMAGE} ... ${COLOR_RESET}"

# Build the docker image
DOCKER_BUILD=$(docker build -t ${DOCKER_IMAGE} . -f docker/nginx/Dockerfile.nginx_hugo)

# Log the docker image build status
if ${DOCKER_BUILD}; then
    echo "${ON_GREEN} SUCCESS ${COLOR_RESET} ${CYAN} Docker image built successfully. ${COLOR_RESET}"
else
    echo "${ON_RED} ERROR ${COLOR_RESET} ${CYAN} Docker image build failed. ${COLOR_RESET}"
    exit 1
fi

# Deploy the container to Cloud Run
# gcloud run deploy mandelbrot_docs --image pulanski/nginx_hugo:0.0.1
# --platform managed --region us-central1 --allow-unauthenticated --project=plum-oss
