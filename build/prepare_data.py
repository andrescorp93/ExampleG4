import os
import numpy as np
import matplotlib.pyplot as plt

borderx = []
bordery = []
borderz = []

# ax = plt.figure().add_subplot(projection='3d')

n = 10

# for k in range(n):
    # os.system("./exampleG4 ../vis.mac")
track = np.loadtxt('distribution.dat', dtype=[('partID', '<i2'), ('trackID', '<i2'),
                                        ('partname', 'S2'), ('procName', 'S14'),
                                        ('denergy, eV', '<f8'), ('positionX, um', '<f8'),
                                        ('positionY, um', '<f8'), ('positionZ, um', '<f8')], delimiter='\t', skiprows=1)

particles = set(track['partID'])
tracks = set(track['trackID'])

for id0 in particles:
    for id1 in tracks:
        single_track_x = np.array([track[i]['positionX, um'] for i in range(len(track)) if track[i]['partID'] == id0 and track[i]['trackID'] == id1])
        single_track_y = np.array([track[i]['positionY, um'] for i in range(len(track)) if track[i]['partID'] == id0 and track[i]['trackID'] == id1])
        single_track_z = np.array([track[i]['positionZ, um'] for i in range(len(track)) if track[i]['partID'] == id0 and track[i]['trackID'] == id1])
        if len(single_track_x) != 0:
            plt.plot(single_track_x, single_track_z)
                # ax.plot(single_track_x, single_track_y, single_track_z)
                # ax.plot(single_track_x, single_track_y, np.zeros(len(single_track_z)), color='blue')
                # ax.plot(single_track_x, np.zeros(len(single_track_y)), single_track_z, color='red')
                # ax.plot(np.zeros(len(single_track_x)), single_track_y, single_track_z, color='green')

    # borderx.append(np.min(track['positionX, um']))
    # borderx.append(np.max(track['positionX, um']))
    # bordery.append(np.min(track['positionY, um']))
    # bordery.append(np.max(track['positionY, um']))
    # borderz.append(np.min(track['positionZ, um']))
    # borderz.append(np.max(track['positionZ, um']))

# ax.set_xlim(np.min(np.array(borderx)), np.max(np.array(borderx)))
# ax.set_ylim(np.min(np.array(bordery)), np.max(np.array(bordery)))
# ax.set_zlim(np.min(np.array(borderz)), np.max(np.array(borderz)))

plt.show()
