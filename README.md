# ExampleGPUPowerMeasurement

Simple example on how to do, in a non-invasive way, GPU power measurements on the JUWELS Booster module. Four processes per node are launched and work with the four GPUs per node, and a fifth process is launched (on just one of all the nodes allocated by the job), not linked to any GPU, which retrieves power.draw via nvidia-smi. This fifth process is carefully spawned such that it doesn't interfere with the other four processes within the node where it lives.

Using a bit more specific SLURM jargon:

 -- a single job is launched (see example_batch.job)

 -- two job steps are launched within that job (see example_batch.job)

 -- job step #1 : single node, single process, calls nvidia-smi and specifies power.draw (see sense_power_gpu.sh). The SLURM flag --exact allows for the job steps to use non-all allocated job resources. IMPORTANT : --mem also helps in having two job steps running in parallel

 -- job step #2 : the main job step, which will probably run MPI with GPU usage (see sample.sh and basic_mpi_program.c)
