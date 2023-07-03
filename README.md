# yarpGPT

A basic yarp wrapper for Azure chatgpt apis.

# Installation

```sh
git clone https://github.com/fbrand-new/yarpGPT.git
cd yarpGPT
./docker/build_docker.sh <my_img_name>
```

# Usage

### Nws

Make sure you have a running `yarpserver`.

Via terminal, you can do
```sh
./docker/start_docker.sh <my_img_name>
yarprobotinterface --context yarpGPT --config GPTDevice.xml
```

This opens a rpcPort `/chat/rpc` that is attached to the GPTDevice, which allows the user to interact with chat gpt on yarp.

You can also interact with the device via a GUI by calling `yarpGPT`.

### Nwc and gui

The Nws has a related Nwc which exposes the generic interface ILLM for Large Language Model. We also provide a GUI for the application that works by first inputting the system prompt and then the chat messages to provide a better visual experience for using the device. To run it 