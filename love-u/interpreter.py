from sys import argv

filename = argv[1]

variables = {}

operations = {
    "love-U": "READ",
    "LOVE-u": "PRINT",
    "love-u": "ASSIGN",
}


def process_line(line: str) -> list[str]:
    """  """
    instructions: list[str] = []

    tokens = [tok for tok in line.split(" ")]
    for token in tokens:
        if token in operations:
            instructions.append(operations[token])
        else:
            instructions.append(token)

    return instructions


def interpet(instructions: list[str]) -> None:
    i, length = 0, len(instructions)
    while i < length:
        # ['Love-u', 'ASSING', 'READ', 'PRINT', 'Love-u']
        # ['ASSIGN', 'Love-u', 'READ', 'PRINT', 'Love-u']
        match instructions[i]:
            case "ASSIGN":
                var_name = instructions[i + 1]
                thing = instructions[i + 2]
                if thing == "READ":
                    variables[var_name] = input("I love you 💕: ")
                else:
                    variables[var_name] = variables.get(thing, thing)
                i += 2
            case "READ":
                input("I love you 💕: ")
            case "PRINT":
                var_name = instructions[i + 1]
                print("💕 " + variables[var_name] + " 💕")
                i += 1
            case _:
                print("I don't love you")
        i += 1


with open(filename) as f:
    code = f.readlines()

code = [line.strip() for line in code[1:] if line.strip()]

instructions = []

for line in code:
    instructions.extend(process_line(line))

interpet(instructions)
