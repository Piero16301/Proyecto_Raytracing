#!/bin/bash
#BATCH -J p1
#SBATCH -N 1
#SBATCH --tasks-per-node=8
#SBATCH --mem=32GB

./Advanced_Raytracer
