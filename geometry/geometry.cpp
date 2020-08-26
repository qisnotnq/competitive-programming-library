vector<pair<double, double>> circle_intersections(double cx1, double cy1, double r1, double cx2, double cy2, double r2) {
    double dx = cx2 - cx1;
    double dy = cy2 - cy1;
    double dx_2 = dx * dx;
    double dy_2 = dy * dy;
    double d_2 = dx_2 + dy_2;
    double d = sqrt(d_2);
    if (d > r1 + r2 || d < abs(r1 - r2)) {
        return { };
    }
    double r1_2 = r1 * r1;
    double r2_2 = r2 * r2;
    double D = r1_2 * r2_2 - pow(r1_2 + r2_2 - d_2, 2) / 4;
    if (D < 0) {
        return { };
    }
    double C = (r1_2 - r2_2) / d_2;
    double Ax = ((cx1 + cx2) + dx * C) / 2;
    double Ay = ((cy1 + cy2) + dy * C) / 2;
    double E = sqrt(D) / d_2;
    double Bx = dy * E;
    double By = dx * E;
    double x1 = Ax + Bx;
    double x2 = Ax - Bx;
    double y1 = Ay - By;
    double y2 = Ay + By;
    return { make_pair(x1, y1), make_pair(x2, y2) };
}
