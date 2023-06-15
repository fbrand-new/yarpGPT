# yarpGPT

A basic yarp wrapper for OpenAI chatgpt apis.

## Testing

### Unit tests

**Python Api** 

Run `<path-to-yarpGPT>/run_unit_test.sh`. 

### Integration test

Make sure you have an up-to-date image or build it using `docker/build_docker.sh`. Then run `docker compose -f docker/docker-compose-test.yml`. A passing test will yield an OK message at the end of the execution.