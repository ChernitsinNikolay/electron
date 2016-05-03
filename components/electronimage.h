#ifndef ELECTRONIMAGE_H
#define ELECTRONIMAGE_H
#include <vector>
#include <string>

namespace Basic {
    class ImageItem
    {
    public:
        enum Axis {
            X,
            Y
        };

        ImageItem() { }
        virtual std::string parse(std::string token, size_t *idx) = 0;
        virtual void rotate(float angle) = 0;
        virtual void reflect(Axis axis) = 0;
    };

    class Point : public ImageItem
    {
    public:
        Point();

        Point operator=(const Point &point);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        float m_x, m_y;
    };

    class Rectangle : public ImageItem
    {
    public:
        Rectangle();

        Rectangle operator=(const Rectangle &rect);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        Point pos;
        float width, height;
    };

    class Arc : public ImageItem
    {
    public:
        Arc();

        Arc operator=(const Arc &arc);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        Rectangle rect;
        float startAngle, sweepAngle;
    };

    class Line : public ImageItem
    {
    public:
        Line();

        Line operator=(const Line &line);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        Point start, end;
    };

    class Arrow : public ImageItem
    {
    public:
        Arrow();

        Arrow operator=(const Arrow &arrow);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        Line line;
        float h;
    };

    class String : public ImageItem
    {
    public:
        String();

        String operator=(const String &string);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        Point point;
        std::string str;
    };

    class Join : public ImageItem
    {
    public:
        Join();

        Join operator=(const Join &join);
        virtual std::string parse(std::string token, size_t *idx);
        virtual void rotate(float angle);
        virtual void reflect(Axis axis);

    private:
        Point pos;
    };
}

class ElectronImage
{
public:
    typedef Basic::ImageItem::Axis Axis;
    typedef std::vector<Basic::Rectangle> Rectangles;
    typedef std::vector<Basic::Arc> Arcs;
    typedef std::vector<Basic::Line> Lines;
    typedef std::vector<Basic::Arrow> Arrows;
    typedef std::vector<Basic::String> Strings;
    typedef std::vector<Basic::Join> Joins;
    typedef std::vector<std::string>::iterator vsit;

    ElectronImage();

    bool parse(const vsit &begin, const vsit &end);

    ElectronImage &operator=(const ElectronImage &item);
    void rotate(float angle);
    void reflect(Axis axis);

    inline const Rectangles &rectangles() const { return m_rects; }
    inline const Arcs &arcs() const { return m_arcs; }
    inline const Lines &lines() const { return m_lines; }
    inline const Arrows &arrows() const { return m_arrows; }
    inline const Strings &strings() const { return m_strings; }
    inline const Joins &joins() const { return m_joins; }

private:
    Rectangles m_rects;
    Arcs m_arcs;
    Lines m_lines;
    Arrows m_arrows;
    Strings m_strings;
    Joins m_joins;
};

#endif // ELECTRONIMAGE_H
