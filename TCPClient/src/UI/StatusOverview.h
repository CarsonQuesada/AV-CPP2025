#pragma once

struct UILayout;

class StatusOverview
{
public:
    StatusOverview(UILayout& layout);
    ~StatusOverview() = default;

    void onUpdate();
private:
    UILayout& layout;
};