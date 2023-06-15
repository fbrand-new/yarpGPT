# yarpGPT

A basic yarp wrapper for Azure chatgpt apis.

# Installation

```sh
git clone https://github.com/fbrand-new/yarpGPT.git
cd yarpGPT
./docker/build_docker.sh <my_img_name>
```

# Usage

Make sure you have a running `yarpserver`.

Via terminal, you can do
```sh
./docker/start_docker.sh <my_img_name>
yarpGPT
```

This opens a rpcPort `/yarpGPT/text:i` which you can access for example via `yarp rpc /yarpGPT/text:i` and start writing a prompt. The service will call gpt apis and send you an answer.