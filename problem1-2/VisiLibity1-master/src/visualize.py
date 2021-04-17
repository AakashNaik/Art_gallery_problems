from shapely.geometry import Point,LineString,Polygon,MultiPoint,MultiLineString,MultiPolygon
from pprint import pprint
import geopandas as gpd
# other constructor, does not work (no hole) :
outer = Polygon(((0,0),(10,0),(10,10),(0,10),(0,0)))
inners = (Polygon(((4,4),(4,6),(6,6),(6,4),(4,4))), )
pol = Polygon(outer.exterior.coords, [inner.exterior.coords for inner in inners])
p = gpd.GeoSeries(pol)
p.plot()
plt.show()