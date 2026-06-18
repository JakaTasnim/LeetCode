class Solution {
public:
    double angleClock(int hour, int minutes) {
        if (hour == 12)
        hour = 0;

        double hourAngle = hour * 30.0 + minutes * 0.5;
        double minuteAngle = minutes * 6.0;

        double angle = abs(hourAngle - minuteAngle);

        return min(angle, 360.0 - angle);
    }
};