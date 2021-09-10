#pragma once

#include "TNAH/Renderer/Texture.h"

namespace tnah {
    /**
     * @headerfile UI.h
     * @author Bryce Standley
     * @date 01/09/2021
     *
     * @brief UI elements based on ImGui. Predefined wrappers to make creating UI faster and more consistent
     *  this class is designed to wrap as many ImGui functions and controls under the UI name, simplifying functions
     *  but also making the API more flexible with what it can do and what values it can take
     */
    class UI
    {
    public:
        //*********************** Enums  ++++++++++++++++++++++++++++++++//
        enum class SeparatorStyle
        {
            Line = 0, Space = 1
        };

        enum class LineFlag
        {
            SameLine = 0, NextLine = 1
        };

        enum class FileBrowserMode
        {
            Open = 0, Save = 1
        };

        

        //*********************** Text ++++++++++++++++++++++++++++++++//
        static void Entry(const char* format, ...);
        static void Entry(const std::string& text);
        static void Entry(const char* text, bool wrapped = false);
        static void Entry(const std::string& text, bool wrapped = false);
        
        //*********************** Input Controls ++++++++++++++++++++++++++++++++//
        static bool Entry(const char* label, std::string& value, bool readOnly = false, bool error = false);
        static bool Entry(const std::string& label, std::string& value, bool readOnly = false, bool error = false);

        static bool Entry(const char* label, float& value, bool readOnly = false, bool error = false);
        static bool Entry(std::string& label, float& value, bool readOnly = false, bool error = false);
        
        static bool Entry(const char* label, int& value, bool readOnly = false, bool error = false);
        static bool Entry(std::string& label, int& value, bool readOnly = false, bool error = false);

        static bool Entry(const char* label, bool& value, bool readOnly = false);
        static bool Entry(std::string& label, bool& value, bool readOnly = false);
        
        static bool Entry(const char* label, glm::vec2& value, bool readOnly = false, float resetValue = 0.0f);
        static bool Entry(std::string& label, glm::vec2& value, bool readOnly = false, float resetValue = 0.0f);

        static bool Entry(const char* label, glm::vec3& value, bool readOnly = false, float resetValue = 0.0f);
        static bool Entry(std::string& label, glm::vec3& value, bool readOnly = false, float resetValue = 0.0f);

        static bool Entry(const char* label, glm::vec4& value, bool readOnly = false, float resetValue = 0.0f);
        static bool Entry(std::string& label, glm::vec4& value, bool readOnly = false, float resetValue = 0.0f);

        //*********************** Slider Controls ++++++++++++++++++++++++++++++++//
        static bool EntrySlider(const char* label, int& value, bool readOnly = false, int min = 0, int max = 0, int resetValue = 0);
        static bool EntrySlider(const std::string& label, int& value, bool readOnly = false, int min = 0, int max = 0, int resetValue = 0);

        static bool EntrySlider(const char* label, float& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntrySlider(const std::string& label, float& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        static bool EntrySlider(const char* label, glm::vec2& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntrySlider(const std::string& label, glm::vec2& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        static bool EntrySlider(const char* label, glm::vec3& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntrySlider(const std::string& label, glm::vec3& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        static bool EntrySlider(const char* label, glm::vec4& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntrySlider(const std::string& label, glm::vec4& value, bool readOnly = false, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        //*********************** Drag Controls ++++++++++++++++++++++++++++++++//
        static bool EntryDrag(const char* label, int& value, bool readOnly = false, float speed = 1, int min = 0.0f, int max = 0.0f, int resetValue = 0);
        static bool EntryDrag(const std::string& label, int& value, bool readOnly = false, int speed = 1, int min = 0.0f, int max = 0.0f, int resetValue = 0);
        
        static bool EntryDrag(const char* label, float& value, bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntryDrag(const std::string& label, float& value, bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        static bool EntryDrag(const char* label, glm::vec2& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntryDrag(const std::string& label, glm::vec2& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        
        static bool EntryDrag(const char* label, glm::vec3& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntryDrag(const std::string& label, glm::vec3& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        
        static bool EntryDrag(const char* label, glm::vec4& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);
        static bool EntryDrag(const std::string& label, glm::vec4& value,bool readOnly = false, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0);

        //*********************** Color Controls ++++++++++++++++++++++++++++++++//
        static bool EntryColor(const char* label, glm::vec3& value, bool readOnly = false);
        static bool EntryColor(const std::string& label, glm::vec3& value, bool readOnly = false);

        static bool EntryColor(const char* label, glm::vec4& value, bool readOnly = false);
        static bool EntryColor(const std::string& label, glm::vec4& value, bool readOnly = false);

        //*********************** Checkbox Controls ++++++++++++++++++++++++++++++++//
        static bool EntryCheckbox(const char* label, bool& value, bool readOnly = false);
        static bool EntryCheckbox(const std::string& label, bool& value, bool readOnly = false);

        
        //*********************** Organisation Controls ++++++++++++++++++++++++++++++++//
        static bool EntryDropdown(const char* label, const char** options, uint32_t optionCount, uint32_t* selectedOption);
        static bool EntryDropdown(const std::string& label, const char** options, uint32_t optionCount, uint32_t* selectedOption);
        static bool EntryDropdown(const char* label, const std::vector<std::string>& options, uint32_t optionCount, uint32_t* selectedOption);
        static bool EntryDropdown(const std::string& label, const std::vector<std::string>& options, uint32_t optionCount, uint32_t* selectedOption);

        static bool EntryCollapsable(const char* label);
        static bool EntryCollapsable(const std::string& label);

        static bool BeginTable(const char* label, int columnCount, ImGuiTableFlags flags = 0);
        static bool BeginTable(const std::string& label, int columnCount, ImGuiTableFlags flags = 0);
        static void EndTable();

        //*********************** Images ++++++++++++++++++++++++++++++++//
        static void Image(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_color = ImVec4(1,1,1,1), const ImVec4& border_color = ImVec4(0,0,0,0));

        //*********************** Buttons ++++++++++++++++++++++++++++++++//
        static bool Button(const std::string& label, const ImVec2& size = ImVec2(0,0));
        static bool Button(const char* label, const ImVec2& size = ImVec2(0,0));
        
        static bool ImageButton(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_color = ImVec4(0,0,0,0), const ImVec4& tint_color = ImVec4(1,1,1,1));

        //*********************** Misc Begins/Ends + ID/Style/Colors ++++++++++++++++++++++++++++++++//
        static void BeginDockingWindow(const std::string& label, bool& open, ImGuiWindowFlags flags = 0);
        static void EndDockingWindow();

        static void BeginWindow(const char* label, bool& open, ImGuiWindowFlags flags = 0);
        static void BeginWindow(const std::string& label, bool& open, ImGuiWindowFlags flags = 0);
        static void EndWindow();

        /**
         * @brief A sub window of another window. Visibility is controlled by the parent window.
         */
        static void BeginSubWindow(const std::string& label, ImVec2 size = {0,0}, bool border = false, ImGuiWindowFlags flags = 0);

        /**
        * @brief A sub window of another window. Visibility is controlled by the parent window.
        */
        static void BeginSubWindow(const char* label, ImVec2 size = {0,0}, bool border = false, ImGuiWindowFlags flags = 0);
        static void EndSubWindow();
        

        
        static bool BeginMenuBar();
        static void EndMenuBar();
        static bool BeginSubMenu(const std::string& label);
        static bool BeginSubMenu(const char* label);
        static void EndSubMenu();
        static bool EntryMenu(const char* label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);
        static bool EntryMenu(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);
        static bool EntryMenu(const std::string& label, const std::string& shortcut = "", bool selected = false, bool enabled = true);

        static void EntrySeparator(SeparatorStyle style = SeparatorStyle::Line);
        static void EntryLine(LineFlag flag = LineFlag::NextLine);

        static void PushID(ImGuiStyleVar id);
        static void PopID();
        
        static void PushStyle(ImGuiStyleVar idx, ImVec2 value);
        static void PushStyle(ImGuiStyleVar idx, float value);
        static void PopStyle(int count = 0);

        static void PushColor(ImGuiColorEditFlags idx, ImVec4 value);
        static void PopColor(int count = 0);

        //*********************** Window Set/Get Properties ++++++++++++++++++++++++++++++++//
        static bool IsFocused();
        
        static void SetWindowPosition(const ImVec2& position = ImVec2(0,0));
        static void SetWindowPosition(const glm::vec2& position = glm::vec2(0,0));
        static void SetWindowPosition(const float& x = 0, const float& y = 0);
        static glm::vec2 GetWindowPosition();

        /**
         * @brief Gets the upper left position of the current window
         */
        static glm::vec2 GetWindowMinPosition();

        /**
        * @brief Gets the bottom right position of the current window
        */
        static glm::vec2 GetWindowMaxPosition();
        
        static void SetWindowSize(const ImVec2& size = ImVec2(0,0));
        static void SetWindowSize(const glm::vec2& size = glm::vec2(0,0));
        static void SetWindowSize(const float& x = 0, const float& y = 0);
        static glm::vec2 GetWindowSize();

        static void SetCursorPosition(const ImVec2& position = ImVec2(0,0));
        static void SetCursorPosition(const glm::vec2& position = glm::vec2(0,0));
        static void SetCursorPosition(const float& x = 0, const float& y = 0);

        static void SetWindowAlpha(const float& alpha = 0);
        static void SetWindowBackgroundColor(const ImVec4& bg_color = ImVec4(0,0,0,0));
        static void SetWindowBackgroundColor(const glm::vec4& bg_color = glm::vec4(0,0,0,0));
        static void SetWindowBackgroundColor(const glm::vec3& bg_color = glm::vec3(0,0,0), const float& alpha = 0);

        static void SetWindowRounding(const float& value);
        static void SetWindowPadding(const ImVec2& value);
        static void SetWindowPadding(const glm::vec2& value);
        static void ClearWindowRounding();
        static void ClearWindowPadding();
        
        static glm::vec2 GetContentSpaceAvailable();

        //*********************** Button Set Properties ++++++++++++++++++++++++++++++++//
        /**
         * @brief Sets idle, hover and pressed colors for a button.
         *  @warning Clear with UI::ClearButtonColors()
         */
        static void SetButtonColors(const ImVec4& idleColor, const ImVec4& hoverColor, const ImVec4& pressedColor);
        
        /** @copydoc UI::SetButtonColors() */
        static void SetButtonColors(const glm::vec4& idleColor, const glm::vec4& hoverColor, const glm::vec4& pressedColor);

        /**
        * @brief Sets a given state color for a button
        *  @warning Clear with UI::ClearButtonColor()
        */
        static void SetButtonStateColor(const ImVec4& color, ImGuiCol buttonState = ImGuiCol_Button);
        /** @copydoc UI::SetButtonStateColor() */
        static void SetButtonStateColor(const glm::vec4& color, ImGuiCol buttonState = ImGuiCol_Button);

        /**
        * @brief Sets a single state color for a button
        *  @warning Clear with UI::ClearButtonXXXColor() where XXX is the state set
        */
        static void SetButtonIdleColor(const ImVec4& color);
        /** @copydoc UI::SetButtonIdleColor() */
        static void SetButtonIdleColor(const glm::vec4& color);
        /** @copydoc UI::SetButtonIdleColor() */
        static void SetButtonHoverColor(const ImVec4& color);
        /** @copydoc UI::SetButtonIdleColor() */
        static void SetButtonHoverColor(const glm::vec4& color);
        /** @copydoc UI::SetButtonIdleColor() */
        static void SetButtonPressedColor(const ImVec4& color);
        /** @copydoc UI::SetButtonIdleColor() */
        static void SetButtonPressedColor(const glm::vec4& color);

        /**
         *  @brief Clear a buttons idle color
         */
        static void ClearButtonIdleColor();
        /**
        *  @brief Clear a buttons hover color
        */
        static void ClearButtonHoverColor();
        /**
        *  @brief Clear a buttons pressed color
        */
        static void ClearButtonPressedColor();

        /**
        *  @brief Clear a button from all colors set
        */
        static void ClearButtonColors();

        /**
        *  @brief Clear a single buttons color style
        */
        static void ClearButtonColor();

        //*********************** Fonts ++++++++++++++++++++++++++++++++//
        static void SetFont(ImFont* font);
        static ImFont* LoadFont(const char* fontPath, float size_pixels);
        static void LoadFonts(const char* rootFontPath, float size_pixels);
        static ImFont* LoadFont(const std::string& fontPath, float size_pixels);
        static void LoadFonts(const std::string& rootFontPath, float size_pixels);
        static std::vector<ImFont*> LoadFonts(const std::vector<std::string>& fontPaths, float size_pixels);
        static std::list<ImFont*> LoadFonts(const std::list<std::string>& fontPaths, float size_pixels);
        static void SetDefaultFont(const char* fontPath, float size_pixels);
        static void SetDefaultFont(ImFont* font);

        
        //*********************** Misc Widgets ++++++++++++++++++++++++++++++++//
        static std::string OpenFileBrowser(const char* browserLabel, const FileBrowserMode& mode = FileBrowserMode::Open, const ImVec2& position = ImVec2(0,0), const char*
                                           validTypes = "*.*");
        static void EntryToggleCheckbox(const char* id, bool& value);
        //TODO: Add functions for the spinners and loading widgets
    
    private:

        //*********************** Control Variables  ++++++++++++++++++++++++++++++++//
        inline static uint32_t s_Counter = 0;
        inline static char s_IDBuffer[16];
        

    };
}
