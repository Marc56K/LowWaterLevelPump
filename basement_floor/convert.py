import numpy
import copy
from stl import mesh

class Main:
    def __init__(self):
        self.points = []
        m = mesh.Mesh.from_file('model.stl')
        for p in m.points:
            self.points.append(p[0:3])
            self.points.append(p[3:6])
            self.points.append(p[6:9])

        self.min_bounds = None
        self.max_bounds = None
        for p in self.points:
            if self.min_bounds == None:
                self.min_bounds = [p[0], p[1], p[2]]
                self.max_bounds = [p[0], p[1], p[2]]
                continue
            for i in range(3):
                if p[i] < self.min_bounds[i]:
                    self.min_bounds[i] = p[i]
                if p[i] > self.max_bounds[i]:
                    self.max_bounds[i] = p[i]
        print("MIN:", self.min_bounds)
        print("MAX:", self.max_bounds)

Main()