using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;

namespace XArrayLocationPlot
{
    class PlotPointInfo
    {
        public string Epc { get; set; }
        public Point PointCoordinates { get; set; }
        public Color PointColor { get; set; }
        public Ellipse RenderedPoint { get; set; }
    }
}
