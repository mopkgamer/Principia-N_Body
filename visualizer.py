import matplotlib.pyplot as plot
import numpy as np

file = open("Output.dat", "r")

lines: list

lines = file.readlines()

xvalues: list[float]
BodyValues: dict[int, list[tuple[float]]]

xvalues = []
BodyValues = {}

for linenr in range(1, len(lines)):
    line = lines[linenr]

    line: str

    if line.startswith("t="):
        xvalues.append(float(line.split("=")[1].removesuffix("s\n")))
    elif line.startswith("Body"):
        index = int(line.split(":")[0].removeprefix("Body"))
        pos = line.split("Position=(")[1].split("),")[0]
        velocity = line.split("Velocity=(")[1].removesuffix(")\n")

        pos = pos.replace(",", "")
        velocity = velocity.replace(",", "")

        yv = []

        for x in pos.split(" "):
            yv.append(float(x))

        try:
            BodyValues[index].append(tuple(yv))
        except Exception:
            BodyValues[index] = [tuple(yv)]

        yv.clear()

        for x in velocity.split(" "):
            yv.append(float(x))
        
        BodyValues[index].append(tuple(yv))

runtime = xvalues[-1]
deltaT = xvalues[0] if len(xvalues) == 1 else xvalues[1] - xvalues[0]

fig, ax = plot.subplots(2, len(BodyValues))

for BodyIdx in BodyValues:
    even_indexed  = [item for i, item in enumerate(BodyValues[BodyIdx]) if i % 2 == 0]
    odd_indexed   = [item for i, item in enumerate(BodyValues[BodyIdx]) if i % 2 == 1]

    ax[BodyIdx, 0].plot(xvalues, even_indexed)
    ax[BodyIdx, 1].plot(xvalues, odd_indexed)

plot.show()