import openai
import os

class OpenAIConf:

    def __init__(self) -> None:
        try:
            openai.api_key = os.getenv("OPENAI_API_KEY")
        except:
            print("Env variable OPENAI_API_KEY is not set. You must set it to use the api.")

class AzureConf(OpenAIConf):

    def __init__(self) -> None:
        openai.api_type = "azure"
        openai.api_version = "2023-05-15" 
        try:
            openai.api_base = os.getenv("OPENAI_API_BASE")  # Your Azure OpenAI resource's endpoint value.
        except:
            print("Env variable OPENAI_API_BASE is not set. \
                        You must set it to use the api within Microsoft Azure.")
        try:
            openai.api_key = os.getenv("OPENAI_API_KEY")
        except:
            print("Env variable OPENAI_API_KEY is not set. You must set it to use the api.")
        super().__init__()
