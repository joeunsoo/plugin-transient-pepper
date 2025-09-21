'use client';

import { AppShell, Button, Container, createTheme, Group, Menu, rem, Stack } from '@mantine/core';
import { mantineSpace, paletteMantine, primaryMain } from './define';

// console.log(DEFAULT_THEME);

const CONTAINER_SIZES: Record<string, number> = {
  xs: 400,
  sm: 540,
  md: 720,
  lg: 960,
  xl: 1520,
};

export const theme = createTheme({
  breakpoints: {
    xs: '36em',
    sm: '52em',
    md: '62em',
    lg: '75em',
    xl: '88em',
  },

  fontFamily:
    '"Pretendard Variable", Pretendard, -apple-system, BlinkMacSystemFont, system-ui, Roboto, "Helvetica Neue", "Segoe UI", "Apple SD Gothic Neo", "Noto Sans KR", "Malgun Gothic", "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", sans-serif',
  fontSizes: {
    xs: 'calc(0.75rem * var(--mantine-scale))',
    sm: 'calc(0.875rem * var(--mantine-scale))',
    md: 'calc(1rem * var(--mantine-scale))',
    lg: 'calc(1.125rem * var(--mantine-scale))',
    xl: 'calc(1.25rem * var(--mantine-scale))',
  },
  headings: {
    fontFamily: 'var(--font-heading)',
    fontWeight: '700',
    sizes: {
      h1: { fontSize: 'calc(2.25rem * var(--mantine-scale))', lineHeight: '1.2' },
      h2: { fontSize: 'calc(1.875rem * var(--mantine-scale))', lineHeight: '1.3' },
      h3: { fontSize: 'calc(1.5rem * var(--mantine-scale))', lineHeight: '1.35' },
      h4: { fontSize: 'calc(1.25rem * var(--mantine-scale))', lineHeight: '1.4' },
      h5: { fontSize: 'calc(1.0rem * var(--mantine-scale))', lineHeight: '1.45' },
      h6: { fontSize: 'calc(0.875rem * var(--mantine-scale))', lineHeight: '1.5' },
    },
  },
  lineHeights: {
    xs: '1.4',
    sm: '1.45',
    md: '1.55',
    lg: '1.6',
    xl: '1.65',
  },

  defaultRadius: 'sm',
  radius: {
    xs: 'calc(0.125rem * var(--mantine-scale))',
    sm: 'calc(0.25rem * var(--mantine-scale))',
    md: 'calc(0.5rem * var(--mantine-scale))',
    lg: 'calc(1rem * var(--mantine-scale))',
    xl: 'calc(2rem * var(--mantine-scale))',
  },
  other: {},

  white: '#ffffff',
  black: primaryMain,

  autoContrast: true,
  primaryColor: 'primary',
  primaryShade: { light: 6, dark: 8 },
  colors: {
    ...paletteMantine,
  },

  cursorType: 'pointer',

  spacing: {
    xs: 'calc(0.200rem * var(--mantine-scale))',
    sm: 'calc(0.600rem * var(--mantine-scale))',
    md: 'calc(1.000rem * var(--mantine-scale))',
    lg: 'calc(1.500rem * var(--mantine-scale))',
    xl: 'calc(2.200rem * var(--mantine-scale))',
    xxl: 'calc(3.500rem * var(--mantine-scale))',
  },

  components: {
    Group: Group.extend({
      defaultProps: {
        gap: 0,
        wrap: 'nowrap',
      },
    }),

    Stack: Stack.extend({
      defaultProps: {
        gap: 0,
      },
    }),

    AppShell: AppShell.extend({
      defaultProps: {
        withBorder: false,
      },
    }),

    Button: Button.extend({
      defaultProps: {
        fw: 500,
      },
    }),

    Container: Container.extend({
      vars: (_, { size, fluid }) => {
        let containerSize;
        if (fluid) {
          containerSize = '100%';
        } else if (size !== undefined && size in CONTAINER_SIZES) {
          containerSize = rem(CONTAINER_SIZES[size]);
        } else {
          containerSize = rem(size);
        }
        return {
          root: {
            '--container-size': containerSize,
          },
        };
      },
    }),

    Menu: Menu.extend({
      styles: {
        item: {
          paddingTop: rem(mantineSpace * 1.5),
          paddingBottom: rem(mantineSpace * 1.5),
        },
      },
    }),
  },
});
