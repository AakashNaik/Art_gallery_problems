using EarClipperLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EarClipper
{
    class Program
    {
        static void Main(string[] args)
        {
            //Example 1
            // specify polygon points in CCW order
            List<Vector3m> points;
            EarClipping earClipping = new EarClipping();
            var res = earClipping.Result;
            

            //Example 3
            points = new List<Vector3m>()
            {
                new Vector3m(0, 0, 0), new Vector3m(5, 0, 0), new Vector3m(5, 5, 0), new Vector3m(3, 3, 0), new Vector3m(2, 6, 0), new Vector3m(1, 3, 0), new Vector3m(0, 5, 0)
            };

            // specify holes in CW order
            List<List<Vector3m>> holes = new List<List<Vector3m>>();
            Vector3m[] hole = { new Vector3m(2, 3.5, 0), new Vector3m(1.5, 3.5, 0), new Vector3m(2, 4, 0) };
            holes.Add(hole.ToList());

            earClipping = new EarClipping();
            earClipping.SetPoints(points, holes);
            earClipping.Triangulate();
            res = earClipping.Result;
            PrintTriangles(res);
            Console.ReadKey();
        }

        private static void PrintTriangles(List<Vector3m> points)
        {
            Console.WriteLine("Polygon:");
            for (int i = 0; i < points.Count; i += 3)
            {
                Console.WriteLine("Face{0}: {1} {2} {3}", i / 3, points[i], points[i+1], points[i+2]);
            }
            Console.WriteLine();
        }
    }
}
