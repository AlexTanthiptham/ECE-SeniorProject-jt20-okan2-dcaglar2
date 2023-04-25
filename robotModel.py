import math

class DifferentialDriveRobot:
    def __init__(self, wheel_radius, wheel_distance):
        self.wheel_radius = wheel_radius
        self.wheel_distance = wheel_distance
    
    def forward_kinematics(self, left_wheel_velocity, right_wheel_velocity, delta_time):
        # Calculate the linear and angular velocity of the robot
        linear_velocity = (left_wheel_velocity + right_wheel_velocity) / 2
        angular_velocity = (1/ self.wheel_distance) * (right_wheel_velocity - left_wheel_velocity)
        print(f"omega:{angular_velocity}| lv:{linear_velocity}")
        # Calculate the change in pose of the robot
        delta_y = linear_velocity * math.cos(angular_velocity * delta_time / 2) * delta_time
        delta_x = linear_velocity * math.sin(angular_velocity * delta_time / 2) * delta_time
        delta_theta = angular_velocity * delta_time

        return delta_x, delta_y, delta_theta
