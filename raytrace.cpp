#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hitable.hpp"
#include "hitablelist.hpp"
#include "camera.hpp"
#include <cstdlib>

vec3 color(const ray &r, hitable *world)
{
    hit_record rec;
    if (world->hitpoint(r, 0.0, MAXFLOAT, rec)) {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    } else {
        vec3 unit_dir = unit_vector(r.direction());
        float t = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 1000;
    int ny = 500;
    int ns = 50;
    std::cout << "P3\n" << nx << " " << ny << "\n200\n";
    vec3    lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3    vertical(0.0, 2.0, 0.0);
    vec3    horizontal(4.0, 0.0, 0.0);
    vec3    origin(0.0, 0.0, 0.0);
    hitable *arr[5];
    arr[0] = new sphere(vec3(0,0,-1), 0.5);
    arr[1] = new sphere(vec3(0,-100,-4), 100);
    camera cam;
    arr[2] = new sphere(vec3(-0.5, 0.5,-1), 0.2);
    arr[3] = new sphere(vec3(0.5, 0.5,-1), 0.2);
    arr[4] = new sphere(vec3(0, 20.7,-1), 20);
    hitable *screen = new hit_list(arr, 5);
    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            vec3 col = vec3(0.0, 0.0, 0.0);
            for (int s = 0; s < ns; s++)
            {
                double u = double(i + drand48()) / double(nx);
                double v = double(j + drand48()) / double(ny);
                ray r = cam.get_ray(u, v);
                
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, screen);
            }
            col /= double(ns);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}