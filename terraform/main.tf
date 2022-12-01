# Setup Google Cloud Run Service for Hugo-based documentation site

# Project ID within Google Cloud
variable "project_id" {
  type    = string
  default = "bazel-llvm-docs"
}

# Project name within Google Cloud
variable "project_name" {
  type    = string
  default = "bazel-llvm-docs"
}

# Region within Google Cloud to deploy to
variable "region" {
  type    = string
  default = "us-east1"
}

# Zone within Google Cloud to deploy to
variable "zone" {
  type    = string
  default = "us-east1-b"
}

terraform {
  required_version = ">= 0.14"

  required_providers {
    # Cloud Run support was added on 3.3.0
    google = ">= 3.3"
  }
}

# Configure the Google Cloud provider
provider "google" {
  project = var.project_id
  region  = var.region
  zone    = var.zone
}

# Enable the Cloud Run API
resource "google_project_service" "run_api" {
  service = "run.googleapis.com"

  disable_on_destroy = true
}

# Create the Cloud Run service
resource "google_cloud_run_service" "docs" {
  name     = var.project_name
  location = var.region

  template {
    spec {
      containers {
        image = "gcr.io/google-samples/hello-app:1.0"
      }
    }
  }

  traffic {
    percent         = 100
    latest_revision = true
  }

  # Waits for the Cloud Run API to be enabled
  depends_on = [google_project_service.run_api]
}

# Allow unauthenticated users to invoke the service
resource "google_cloud_run_service_iam_member" "run_all_users" {
  service  = google_cloud_run_service.docs.name
  location = google_cloud_run_service.docs.location
  role     = "roles/run.invoker"
  member   = "allUsers"
}

# Display the service URL
output "service_url" {
  value = google_cloud_run_service.docs.status[0].url
}

# # Configure the Google Cloud Run provider
# provider "google-beta" {
#   project = var.project
#   region  = var.region
# }

# # Create a Google Cloud Storage bucket for the Hugo site
# resource "google_storage_bucket" "docs" {
#   name          = "docs-${var.project}"
#   location      = var.region
#   force_destroy = true
# }
