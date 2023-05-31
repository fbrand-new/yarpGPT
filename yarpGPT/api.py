import yarp
import os
import sys
import openai

class GPTCallback(yarp.BottleCallback):
    def __init__(self,key,context,model="gpt-3.5-turbo"):
        print("initializing")
        self.context = context
        self.model = model
        self.response_port = yarp.BufferedPortBottle()
        self.response_port.open("/yarpGPT/target:o")

        openai.api_key = key
        
        super().__init__()

    def onRead(self,bottle,reader):
        messages = self.create_messages(bottle)
        response = self.answer(messages)
        self.write_response(response)

    def answer(self,messages):
        
        response = openai.ChatCompletion.create(
            model=self.model,
            messages=messages
        )

        return response
    
    def create_messages(self,bottle):
        
        messages = []

        # We suppose that context is a single string
        messages.append({"role": "system", "content": self.context})

        # We take the input from the input bottle.
        # bottle = ("My prompt")
        prompt = bottle.toString()

        messages.append({"role": "user", "content": prompt})

        #TODO: 
        #We need to save the responses and append it back to the messages, keeping an internal state of the conversation. For now it will be "stateless"

        return messages

    def write_response(self,response):
        answer = response['choices'][0]['message']['answer']
        bottle = self.response_port.prepare()
        bottle.addString(answer)
        self.response_port.write()


class yarpGPT(yarp.RFModule):

    def configure(self,rf):

        yarp.Network.init()
        self.period = 0.2
        self.context = rf.find("context").asString()
        self.in_port = yarp.BufferedPortBottle()
        self.in_port.open("/yarpGPT/text:i")
        
        callback = GPTCallback(os.getenv("OPENAI_API_KEY"),self.context)
        self.in_port.useCallback(callback)
        
        return True
    
    def updateModule(self):

        return True