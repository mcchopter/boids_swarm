#pragma once


class obstacle {
    public:
        obstacle();
        obstacle(double start_y, double start_x, double radius);
        ~obstacle();
        void draw();



    private:
        double y, x, radius;
        int r, g, b;
};

