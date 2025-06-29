%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% kaobook
% LaTeX Class
% Version 0.9.7 (2021/06/02)
%
% This template originates from:
% https://www.LaTeXTemplates.com
%
% For the latest template development version and to make contributions:
% https://github.com/fmarotta/kaobook
%
% Authors:
% Federico Marotta (federicomarotta@mail.com)
% Based on the doctoral thesis of Ken Arroyo Ohori (https://3d.bk.tudelft.nl/ken/en)
% and on the Tufte-LaTeX class.
% Modified for LaTeX Templates by Vel (vel@latextemplates.com)
%
% License:
% LPPL (see included MANIFEST.md file)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%----------------------------------------------------------------------------------------
%	CLASS CONFIGURATION
%----------------------------------------------------------------------------------------

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{kaobook}[2021/06/02 v0.9.7 kaobook]
\newcommand{\@baseclass}{scrbook} % Base class name

%\RequirePackage{kvoptions} % Manage class key-value options

%\SetupKeyvalOptions{
%    family = kao,
%    prefix = kao@
%}

% Set the default options
\PassOptionsToClass{a4paper}{\@baseclass}
\PassOptionsToClass{fontsize=10pt}{\@baseclass}
\PassOptionsToClass{parskip=half}{\@baseclass}
\PassOptionsToClass{headings=optiontoheadandtoc}{\@baseclass}

% Pass through any other options to the base class
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{\@baseclass}} 

%\ProcessKeyvalOptions*
\ProcessOptions\relax % Process the options

\LoadClass{\@baseclass} % Load the base class

% Define kao-specific options
%\DeclareStringOption[1]{secnumdepth}
\DefineFamily{kao}
\DefineFamilyMember[kaobook]{kao}
\DefineFamilyKey[kaobook]{kao}{secnumdepth}[1]{\setcounter{secnumdepth}{#1}\FamilyKeyStateProcessed}
\FamilyProcessOptions[kaobook]{kao}

\RequirePackage{styles/kaoCJKsc} % Load the code common to all classes

%----------------------------------------------------------------------------------------
%	FRONT-, MAIN-, BACK- MATTERS BEHAVIOUR
%----------------------------------------------------------------------------------------

% Front matter
\let\oldfrontmatter\frontmatter % Store the old command
\renewcommand{\frontmatter}{%
	\oldfrontmatter% First of all, call the old command
	\pagestyle{plain.scrheadings}% Use a plain style for the header and the footer
	\pagelayout{wide}% Use a wide page layout
	\setchapterstyle{plain} % Choose the default chapter heading style
	% \sloppy % Required to better break long lines
}

%------------------------------------------------

% Main matter
\let\oldmainmatter\mainmatter % Store the old command
\renewcommand{\mainmatter}{%
    \oldmainmatter% Call the old command
	\pagestyle{scrheadings}% Use a fancy style for the header and the footer
	\pagelayout{margin}% Use a 1.5 column layout
	\setchapterstyle{kao} % Choose the default chapter heading style
}

%------------------------------------------------

% Appendix
\let\oldappendix\appendix% Store the old command
\renewcommand{\appendix}{%
	\oldappendix% Call the old command
	\bookmarksetup{startatroot}% Reset the bookmark depth
}

%------------------------------------------------

% Back matter
\let\oldbackmatter\backmatter% Store the old command
\renewcommand{\backmatter}{%
	\oldbackmatter% Call the old command
	\bookmarksetup{startatroot}% Reset the bookmark depth
	\pagestyle{plain.scrheadings}% Use a plain style for the header and the footer
	\pagelayout{wide}% Use a wide page layout
	\setchapterstyle{plain} % Choose the default chapter heading style
}

%----------------------------------------------------------------------------------------
%	PART STYLES REVISED
%----------------------------------------------------------------------------------------
\renewcommand*{\raggedpart}{\raggedsection} % 使PART部分的标题左对齐
% 设定标题与页面顶端的距离为 5cm
\RedeclareSectionCommand[
  beforeskip=5cm, % 距离页面顶端 5cm
  innerskip=0em, % 距离标题下方 2.5cm
]{part}
\renewcommand*{\partformat}{\color{titlecolorcoverpage}\small{第~\thepart~部分}}

\DeclareDocumentCommand{\addpartwithbg}{ m m }{
    % m = 必选参数: 分部的标题文本
    % m = 必选参数: 背景图片的路径
	\pagelayout{wide} % 无边距
    \AddToShipoutPictureBG*{%
	\AtPageLowerLeft{%
	\adjustbox{width=1.1\paperwidth, height=1.5\paperheight, keepaspectratio}{% 强制图片至纸张尺寸，但可能裁切
		\includegraphics{#2}
				}
					}
    }
    \part{#1}
	\pagelayout{margin} % 恢复边距
} 

%----------------------------------------------------------------------------------------
%	CHAPTER HEADING STYLES
%----------------------------------------------------------------------------------------

\DeclareDocumentCommand{\setchapterstyle}{m}{%
	% 根据输入参数设置章节样式
	\ifthenelse{\equal{plain}{#1}}{\chapterstyleplain}{}
    \ifthenelse{\equal{bar}{#1}}{\chapterstylebar}{}
	\ifthenelse{\equal{lines}{#1}}{\chapterstylelines}{}
    \ifthenelse{\equal{kao}{#1}}{\chapterstylekao}{}
}

% KOMA script的默认定义
\DeclareDocumentCommand{\chapterstyleplain}{}{%
	% 定义章节行格式
	\renewcommand{\chapterlinesformat}[3]{%
		\@hangfrom{##2}{##3}}
	% 定义章节格式
	\renewcommand*{\chapterformat}{%
		\mbox{\chapappifchapterprefix{\nobreakspace}\thechapter%
		\autodot\IfUsePrefixLine{}{\enskip}}}
    % 重新声明章节命令，设置前后间距
    \RedeclareSectionCommand[beforeskip=0cm,afterskip=10\vscale]{chapter}
	% 设置目录偏移量
	\setlength{\mtocshift}{-1\vscale}
}

% 灰色条样式
\DeclareDocumentCommand{\chapterstylebar}{}{%
	% 定义章节格式
	\renewcommand*{\chapterformat}{%
		\mbox{\chapappifchapterprefix{\nobreakspace}\thechapter%
		\autodot\IfUsePrefixLine{}{\enskip}}%
	}
	% 定义章节行格式，使用TikZ绘制灰色条
	\renewcommand{\chapterlinesformat}[3]{%
		\begin{tikzpicture}[remember picture, overlay]
			\node[
				anchor=south west,
				xshift=\dimexpr - \hoffset - \oddsidemargin - 1in -1mm,%-30\hscale,
				yshift=4.3mm,
				rectangle,
				fill=gray!20!white,
				fill opacity=0.8,
				inner ysep=5\vscale,
				inner xsep=\dimexpr \hoffset + \oddsidemargin + 1in,%30\hscale,
				text opacity=1,
				text width=\paperwidth-40\hscale,
			]{\@hangfrom{##2}{##3}};
		\end{tikzpicture}
	}
    % 重新声明章节命令，设置前后间距
    \RedeclareSectionCommand[beforeskip=-55\vscale,afterskip=6\vscale]{chapter}
	% 设置目录偏移量
	\setlength{\mtocshift}{-1\vscale}
}

% 线条样式
\renewcommand{\hrulefill}[1][0.4pt]{%
	\leavevmode\leaders\hrule height #1\hfill\kern\z@%
}
\DeclareDocumentCommand{\chapterstylelines}{}{%
	% 定义章节格式
	\renewcommand*{\chapterformat}{%
		\chapappifchapterprefix{\nobreakspace}\scalebox{3.5}{\thechapter\autodot}%
	}%
	% 定义章节行格式，使用线条分隔
	\renewcommand\chapterlinesformat[3]{%
	  %\vspace*{-1cm}%
	  \leavevmode%
	  \makebox[0pt][l]{%
		\makebox[\textwidth][l]{\hrulefill[1pt]##2}%\hfill%\par%\bigskip
		\makebox[\marginparsep][l]{}%
		\makebox[\marginparwidth][l]{}%
	  }\\
	  %\vspace{.5cm}
	  \makebox[0pt][l]{%
		\makebox[\textwidth][l]{##3}%
		\makebox[\marginparsep][l]{}%
		\makebox[\marginparwidth][l]{}%
	  }\\
	  \makebox[0pt][l]{%
		\makebox[\textwidth+\marginparsep+\marginparwidth][l]{\hrulefill[1.1pt]}%
	  }%
	}%
	% 重新声明章节命令，设置前后间距
	\RedeclareSectionCommand[beforeskip=0cm,afterskip=10\vscale]{chapter}
	% 设置目录偏移量
	\setlength{\mtocshift}{-1\vscale}%
}

% Kao样式
\DeclareDocumentCommand{\chapterstylekao}{}{%
	% 定义章节格式
	\renewcommand*{\chapterformat}{%
		\mbox{\chapappifchapterprefix{\nobreakspace}\scalebox{2.85}{\thechapter\autodot}}%
	}%
	% 定义章节行格式，使用竖线分隔
	\renewcommand\chapterlinesformat[3]{%
		\vspace{3.5\vscale}%
		\if@twoside%
			\Ifthispageodd{%
				\smash{\makebox[0pt][l]{%
					\parbox[b]{\textwidth}{\flushright{##3}}%
					\makebox[\marginparsep][c]{\rule[-2\vscale]{1pt}{27.4\vscale+\f@size mm}}%
					\parbox[b]{\marginparwidth}{##2}%
				}}%
			}{
				\smash{\makebox[\textwidth][r]{%
					\parbox[b]{\marginparwidth}{\flushright{##2}}%
					\makebox[\marginparsep][c]{\rule[-2\vscale]{1pt}{27.4\vscale+\f@size mm}}%
					\parbox[b]{\textwidth}{\flushleft{##3}}%
				}}%
			}
		\else%
			\smash{\makebox[0pt][l]{%
				\parbox[b]{\textwidth}{\flushright{##3}}%
				\makebox[\marginparsep][c]{\rule[-2\vscale]{1pt}{27.4\vscale+\f@size mm}}%
				\parbox[b]{\marginparwidth}{##2}%
			}}%
		\fi%
	}%
	% 重新声明章节命令，设置前后间距
	\RedeclareSectionCommand[beforeskip=0cm,afterskip=10\vscale]{chapter}%
    % 设置目录偏移量
    \setlength{\mtocshift}{-3\vscale}%
}

% 设置章节图片，输入参数为图片路径和可选的"beforeskip"
\DeclareDocumentCommand{\setchapterimage}{O{55\vscale} m}{%
	\setchapterpreamble[o]{%
		\vspace*{-27\vscale}\hspace*{\dimexpr - \hoffset - \oddsidemargin - 1in}%
		\includegraphics[width=\paperwidth,height=#1+27\vscale,keepaspectratio=false]{#2}%
	}%
    \chapterstylebar%
	% beforeskip=-(figure_height-top_margin)
    \RedeclareSectionCommand[beforeskip=-#1, afterskip=6\vscale]{chapter}%
    % 设置目录偏移量
    \setlength{\mtocshift}{0cm}%
}

% 默认使用plain样式
\chapterstyleplain

%----------------------------------------------------------------------------------------
%	FONTS AND STYLES
%----------------------------------------------------------------------------------------

% Set KOMA fonts for book-specific elements
\addtokomafont{part}{\normalfont\scshape\bfseries}
\addtokomafont{partentry}{\normalfont\scshape\bfseries}
\addtokomafont{chapter}{\normalfont\bfseries}
\addtokomafont{chapterentry}{\normalfont\bfseries}

% Set KOMA fonts for elements common to all classes
\addtokomafont{section}{\normalfont\bfseries}
\addtokomafont{subsection}{\normalfont\bfseries}
\addtokomafont{subsubsection}{\normalfont\bfseries}
\addtokomafont{paragraph}{\normalfont\bfseries}
\setkomafont{descriptionlabel}{\normalfont\bfseries}

%----------------------------------------------------------------------------------------
%	TOC, LOF & LOT
%----------------------------------------------------------------------------------------

\PassOptionsToClass{toc=listof}{\@baseclass}
\PassOptionsToClass{toc=index}{\@baseclass}
\PassOptionsToClass{toc=bibliography}{\@baseclass}

%----------------------------------------------------------------------------------------
%	NUMBERING
%----------------------------------------------------------------------------------------

%\setcounter{secnumdepth}{\kao@secnumdepth} % Set section numbering 
%depth

\counterwithin*{sidenote}{chapter} % Uncomment to reset the sidenote counter at each chapter
%\counterwithout{sidenote}{chapter} % Uncomment to have one sidenote counter for the whole document
