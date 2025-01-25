from openai import OpenAI

def generateInfo (my_api_key, type: str) -> str:
    client = OpenAI(api_key = my_api_key)
    completion = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=[
            {"role": "system", "content": "You are a helpful plant information writer. The information would be on the board. You can only write information about given type of plant information. If you recieve unreal plant type, write: " + type + " is not a plant."},
            {"role": "user", "content": "Write brief info about " + type + " plant, most important info (recomended watering, enviroment, etc), no more than 3 sentences"}
        ]
    )
    print(completion.choices[0].message)
    return completion.choices[0].message.content

def generateResponse (my_api_key: str, message: str, type: str) -> str:
    client = OpenAI(api_key = my_api_key)
    completion = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=[
            {"role": "system", "content": "You are a helpful plant assistant. You can only write informational responses about given type of plant information. Your responses must to be no longer than 300 symbols"},
            {"role": "user", "content": "Plant type: " + type + ". Question: " + message}
        ]
    )
    print(completion.choices[0].message)
    return completion.choices[0].message.content

def hello (my_api_key):
    client = OpenAI(api_key = my_api_key)
    completion = client.chat.completions.create(
    model="gpt-4o-mini",
    messages=[
        {"role": "developer", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Write a random number"}
    ]
    )

    print(completion.choices[0].message)
    return completion.choices[0].message.content



def add_numbers(a, b):
    return a + b + a

