# GitHub Release 准备指南

## 需要上传到Release的大文件

以下文件由于超过GitHub 100MB限制，需要通过Release上传：

### 1. 主要文件
- **文件名**: `mathnotes.pdf`
- **大小**: 124MB
- **描述**: 完整的数学笔记PDF文件
- **位置**: 项目根目录

### 2. 数据结构教材
- **文件名**: `数据结构辅导第2版.pdf`
- **大小**: 168MB
- **描述**: 数据结构课程教材
- **位置**: `数据结构/教材/`

### 3. 数理统计教材
- **文件名**: `数理统计学导论（原书第7版）.pdf`
- **大小**: 110MB
- **描述**: 数理统计学教材
- **位置**: `数理统计/教材/`

## Release创建步骤

1. 访问: https://github.com/easygl1der/mathnotes/releases
2. 点击: "Create a new release"
3. 填写版本号: v1.0.0
4. 填写标题: 数学笔记 v1.0.0
5. 上传以上三个文件
6. 点击: "Publish release"

## 建议的Release描述

```markdown
# 数学笔记 v1.0.0

本版本包含完整的数学学习笔记和相关教材。

## 📚 包含内容
- 数学分析笔记
- 复变函数理论
- 实变函数基础
- 近世代数
- 数据结构与算法
- 数理统计学

## 📁 大文件下载
由于GitHub文件大小限制，以下文件通过Release提供：
- `mathnotes.pdf` - 完整笔记合集
- `数据结构辅导第2版.pdf` - 数据结构教材
- `数理统计学导论.pdf` - 统计学教材

## 🔗 在线访问
访问笔记网站: https://easygl1der.github.io/mathnotes/
```

## 文件重命名建议

为了避免文件名编码问题，建议重命名：
- `mathnotes.pdf` → `mathnotes-v1.0.0.pdf`
- `数据结构辅导第2版.pdf` → `data-structures-textbook.pdf`
- `数理统计学导论.pdf` → `mathematical-statistics-textbook.pdf` 