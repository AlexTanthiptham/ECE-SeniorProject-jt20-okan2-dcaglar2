import matplotlib.pyplot as plt
import pandas as pd

def plotPID() :

    # read the CSV file into a pandas DataFrame
    df = pd.read_csv('pid.csv')

    # extract the columns you want to plot
    y1 = df["X_OUT"]
    y2 = df["Y_OUT"]
    y3 = df["A_SPEED"]
    y4 = df["B_SPEED"]
    y5 = df["Y_DIST"]

    y4 = y4[y4 > 0]
    y3 = y3[y3 > 0]

    # create a range of x values with the same length as the other columns
    x = range(len(y1))

    # create a new figure and set the title
    fig, ax = plt.subplots(2,2)
    #ax.set_title('Four Column Plot')

    # plot each column on the same axes
    ax[0,0].set_title("Xout")
    ax[0,1].set_title("Yout")
    ax[1,0].set_title("A wheel speed")
    ax[1,1].set_title("B wheel speed")
    ax[0,0].plot(x, y1, label='X Out')
    ax[0,1].plot(x, y2, label='Y Out')
    ax[1,0].plot(range(0,len(y3)), y3, label='A Wheel Speed From Encoder')
    ax[1,1].plot(range(0,len(y4)), y4, label='B Wheel Speed From Encoder')
    ax[0,1].plot(x, y5, label='Kinect')

    ax[0,1].legend()

    # add a legend to the plot
    #ax.legend()
    plt.tight_layout()
    # show the plot
    plt.savefig("pid.png")

def main() : 
    plotPID()

if __name__ == "__main__" : 
    main()
