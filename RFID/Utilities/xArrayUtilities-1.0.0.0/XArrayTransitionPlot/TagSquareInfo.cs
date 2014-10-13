using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;

namespace XArrayTransitionPlot
{
    class TagSquareInfo
    {
        public ushort Zone { get; set; }
        public string Epc { get; set; }
        public Rectangle RenderedSquare { get; set; }
        public Point SquareCoordinates { get; set; }
        public Color SquareColor { get; set; }
    }
}
