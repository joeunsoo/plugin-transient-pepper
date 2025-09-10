'use client';

import {
  createTheme,
  getContrastRatio,
  darken,
  lighten,
} from '@mui/material/styles';

import {
  noDragSx,
  primaryMain,
  secondaryMain,
  greyMain,
} from '@/define';

export const themeVars = {
  cssVariables: true,

  spacing: (factor: number) => `${0.25 * factor}rem`, // (Bootstrap strategy)

  typography: {
    fontFamily: '"Pretendard Variable", Pretendard, -apple-system, BlinkMacSystemFont, system-ui, Roboto, "Helvetica Neue", "Segoe UI", "Apple SD Gothic Neo", "Noto Sans KR", "Malgun Gothic", "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", sans-serif',
    h1: {
      fontSize: 'var(--mui-fontSize-xl4, 2.25rem)',
      fontWeight: 'var(--mui-fontWeight-xl, 700)'
    },
    h2: {
      fontSize: 'var(--mui-fontSize-xl3, 1.875rem)',
      fontWeight: 'var(--mui-fontWeight-xl, 700)'
    },
    h3: {
      fontSize: 'var(--mui-fontSize-xl2, 1.5rem)',
      fontWeight: 'var(--mui-t-lg, 600)'
    },
    h4: {
      fontSize: 'var(--mui-fontSize-xl, 1.25rem)',
      fontWeight: 'var(--mui-fontWeight-lg, 600)'
    },
    h5: {
      fontSize: 'var(--mui-fontSize-md, 1rem)',
      fontWeight: 'var(--mui-fontWeight-lg, 600)'
    },
  },

  fontWeight: {
    sm: 400,
    md: 500,
    lg: 600,
    xl: 700,
  },

  fontSize: {
    xs: '0.75rem',
    sm: '0.875rem',
    md: '1rem',
    lg: '1.125rem',
    xl: '1.25rem',
    xl2: '1.5rem',
    xl3: '1.875rem',
    xl4: '2.25rem',
    xl5: '2.55rem',
  },
  shape: {
    // borderRadius: 4,
  },
  palette: {
    // mode: 'dark',
    background: {
      // default: '#f2f2f2',
      default: darken(secondaryMain, 0.85),
      paper: darken(primaryMain, 0.75),
    },
    primary: {
      main: primaryMain,
      lightest: lighten(primaryMain, 0.85),
      lightermost: lighten(primaryMain, 0.70),
      lighter: lighten(primaryMain, 0.60),
      lighten: lighten(primaryMain, 0.35),
      light: lighten(primaryMain, 0.2),
      dark: darken(primaryMain, 0.2),
      darken: darken(primaryMain, 0.35),
      darker: darken(primaryMain, 0.60),
      darkermost: darken(primaryMain, 0.70),
      darkest: darken(primaryMain, 0.85),
      contrastText: getContrastRatio(primaryMain, '#fff') > 2.5 ? '#fff' : '#111',
    },
    secondary: {
      main: secondaryMain,
      lightest: lighten(secondaryMain, 0.85),
      lightermost: lighten(secondaryMain, 0.70),
      lighter: lighten(secondaryMain, 0.60),
      lighten: lighten(secondaryMain, 0.35),
      light: lighten(secondaryMain, 0.2),
      dark: darken(secondaryMain, 0.2),
      darken: darken(secondaryMain, 0.35),
      darker: darken(secondaryMain, 0.60),
      darkermost: darken(secondaryMain, 0.70),
      darkest: darken(secondaryMain, 0.85),
      contrastText: getContrastRatio(secondaryMain, '#fff') > 2.5 ? '#fff' : '#111',
    },
    info: {
      main: greyMain,
      lightest: lighten(greyMain, 0.85),
      lightermost: lighten(greyMain, 0.70),
      lighter: lighten(greyMain, 0.60),
      lighten: lighten(greyMain, 0.35),
      light: lighten(greyMain, 0.2),
      dark: darken(greyMain, 0.2),
      darken: darken(greyMain, 0.35),
      darker: darken(greyMain, 0.60),
      darkermost: darken(greyMain, 0.70),
      darkest: darken(greyMain, 0.85),
      contrastText: getContrastRatio(greyMain, '#fff') > 2.5 ? '#fff' : '#111',
    },
    common: {
      white: '#ffffff',
      black: '#000000',
      grey: '#666666',
    },
    text: {
      primary: lighten(primaryMain, 0.85),
      secondary: 'rgba(255, 255, 255, 0.7)',
      disabled: 'rgba(255, 255, 255, 0.5)',
      icon: 'rgba(255, 255, 255, 0.5)',
    },
    divider: 'var(--mui-palette-common-black)',
  },

  components: {
    MuiButton: {
      styleOverrides: {
        root: {
          textTransform: 'none',
        },
      },
    },
    MuiToggleButton: {
      styleOverrides: {
        root: {
          textTransform: 'none',
        },
      },
    },
    MuiIconButton: {
      styleOverrides: {
        root: {
          borderRadius: 4,
        },
      },
    },
    MuiTooltip: {
      styleOverrides: {
        tooltip: {
          ...noDragSx,
        },
      },
    },
    MuiMenu: {
      styleOverrides: {
        root: {
          ...noDragSx,
        },
      },
    },
    MuiTypography: {
      styleOverrides: {
        root: {
          ...noDragSx,
          fontWeight: 'var(--mui-fontWeight-md)',
        },
      },
    }
  },
};

// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore
const theme = createTheme(themeVars);

export default theme;
