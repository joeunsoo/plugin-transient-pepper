'use client';

import {
  createTheme,
} from '@mui/material/styles';

import {
  palette,
} from '@/define';

export const themeVars = {
  cssVariables: true,

  spacing: (factor: number) => `${0.25 * factor}rem`, // (Bootstrap strategy)

  typography: {
    fontFamily: '"Pretendard Variable", Pretendard, -apple-system, BlinkMacSystemFont, system-ui, Roboto, "Helvetica Neue", "Segoe UI", "Apple SD Gothic Neo", "Noto Sans KR", "Malgun Gothic", "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", sans-serif',
  },

  shape: {
    // borderRadius: 4,
  },
  palette: {
    mode: 'dark',
    background: {
      // default: '#f2f2f2',
      default: palette.secondary.blackest,
      paper: palette.primary.darker,
    },
    Tooltip: {
      bg: palette.secondary.darkermost
    },
    primary: palette.primary,
    secondary: palette.secondary,
    info: palette.info,
    common: {
      white: '#ffffff',
      black: '#000000',
      gray: '#666666',
    },
    text: {
      primary: palette.primary.lightest,
      secondary: 'rgba(255, 255, 255, 0.7)',
      disabled: 'rgba(255, 255, 255, 0.5)',
      icon: 'rgba(255, 255, 255, 0.5)',
    },
    divider: 'var(--mantine-color-black)',
  },

  components: {
    MuiButton: {
      styleOverrides: {
        root: {
          textTransform: 'none',
          cursor: 'default',
        },
      },
    },
    MuiToggleButton: {
      styleOverrides: {
        root: {
          textTransform: 'none',
          cursor: 'default',
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
          userSelect: 'none',
          mt:50,
        },
      },
    },
    MuiMenu: {
      styleOverrides: {
        root: {
          userSelect: 'none',
        },
      },
    },
    MuiTypography: {
      styleOverrides: {
        root: {
          userSelect: 'none',
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
