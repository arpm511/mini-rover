# Contributing to Mini Rover

Thank you for your interest in contributing to the Mini Rover project! This document provides guidelines for contributing to this open-source robotics project.

## 🎯 Project Status

This project is actively being developed and is part of a portfolio demonstrating robotics and embedded systems skills. While the rover was originally designed for the DTU RoboCup stair-climbing challenge, it's evolving into a versatile platform for experimentation.

## 🤝 How to Contribute

### Reporting Issues

- **Bug Reports**: Use the issue tracker to report bugs. Include:
  - Clear description of the problem
  - Steps to reproduce
  - Expected vs actual behavior
  - Hardware/software versions
  - Photos or videos if applicable

- **Feature Requests**: Suggest new features or improvements. Explain:
  - The problem you're trying to solve
  - Your proposed solution
  - Why it would benefit the project

### Code Contributions

1. **Fork the Repository**
   ```bash
   git clone https://github.com/YOUR_USERNAME/mini-rover.git
   cd mini-rover
   ```

2. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make Your Changes**
   - Write clear, commented code
   - Follow existing code style
   - Test your changes thoroughly

4. **Commit Your Changes**
   ```bash
   git add .
   git commit -m "Add: Brief description of your changes"
   ```
   
   Commit message prefixes:
   - `Add:` New features or files
   - `Fix:` Bug fixes
   - `Update:` Updates to existing features
   - `Docs:` Documentation changes
   - `Refactor:` Code refactoring

5. **Push and Create Pull Request**
   ```bash
   git push origin feature/your-feature-name
   ```

### Areas Where You Can Help

#### Hardware
- **3D Models**: Improvements to printability, strength, or aesthetics
- **Alternative Parts**: Suggestions for easier-to-source components
- **Assembly Instructions**: Better documentation or videos

#### Software
- **Arduino Sketches**: New control algorithms, sensor integration
- **ROS Integration**: Navigation, mapping, perception improvements
- **Testing**: Hardware-in-the-loop testing, simulation

#### Documentation
- **Assembly Guides**: Step-by-step instructions with photos
- **Troubleshooting**: Common issues and solutions
- **Tutorials**: How to modify or extend the rover
- **Translations**: Documentation in other languages

## 📋 Code Style

### Arduino/C++
- Use descriptive variable names
- Comment complex logic
- Keep functions focused and small
- Use constants instead of magic numbers

### Python (ROS)
- Follow PEP 8 style guide
- Use type hints where applicable
- Document functions with docstrings

### 3D Models
- Export STL files in millimeters
- Include both source files (.blend) and ready-to-print files (.stl)
- Name files descriptively (e.g., `6x_wheel_rim.stl`)

## 🧪 Testing

Before submitting:
- **Hardware**: Test on actual hardware if possible
- **Software**: Compile and test code on target platform
- **Documentation**: Verify links and formatting

## 📝 Documentation

When adding features:
- Update relevant README sections
- Add comments to code
- Include wiring diagrams if adding new hardware
- Document pin configurations and dependencies

## 🔧 Development Setup

### Required Tools
- **3D Printing**: Blender (for model editing), slicer software
- **Electronics**: Arduino IDE or PlatformIO
- **ROS**: ROS Noetic or ROS 2 Humble (for autonomy features)
- **Git LFS**: For handling large binary files

### Git LFS Setup
```bash
git lfs install
git lfs track "*.stl" "*.blend" "*.gcode" "*.step" "*.png" "*.jpg" "*.pdf"
```

## 🌟 Recognition

Contributors will be:
- Listed in a CONTRIBUTORS.md file
- Credited in release notes
- Mentioned in relevant documentation

## ❓ Questions?

- Open an issue for project-related questions
- Tag issues with `question` label
- Check existing issues first to avoid duplicates

## 📜 License

By contributing, you agree that your contributions will be licensed under:
- **Software**: MIT License
- **Hardware**: Creative Commons Attribution-ShareAlike 4.0

## 🙏 Acknowledgments

This project builds upon the Wild Willy design. We appreciate all contributions, big or small!

---

**Thank you for helping make this project better!** 🚀
