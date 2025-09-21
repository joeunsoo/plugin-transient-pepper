import legacy from '@vitejs/plugin-legacy';
import react from '@vitejs/plugin-react-swc';
import { defineConfig } from 'vite';
import checker from 'vite-plugin-checker';
import svgr from 'vite-plugin-svgr';

export default defineConfig({
  base: '/',
  server: {
    open: true,
  },
  plugins: [
    react(),
    svgr(),
    checker({
      typescript: true,
      eslint: {
        useFlatConfig: true, // for me this fix the problem
        lintCommand: 'eslint .',
        dev: {
          logLevel: ['warning', 'error'],
        },
      },
      overlay: {
        initialIsOpen: 'error',
      },
    }),
    // Add the legacy plugin here
    legacy({
      targets: ['defaults', 'not IE 11', 'Safari >= 11'],
      additionalLegacyPolyfills: ['regenerator-runtime/runtime'], // optional, for async/await support
    }),
  ],
  build: {
    outDir: 'build',
    rollupOptions: {
      output: {
        manualChunks: {
          // 예: react 관련 묶기
          react: ['react', 'react-dom', 'react-hook-form'],
          // UI 프레임워크 따로 묶기
          mantine: ['@mantine/core', '@mantine/hooks', '@mantine/notifications', 'chroma-js'],
          emotion: ['@emotion/cache', '@emotion/react', '@emotion/serialize', '@emotion/utils'],
          motion: ['framer-motion'],
        },
      },
    },
  },
  resolve: {
    alias: [
      { find: '@/src', replacement: '/src' },
      { find: '@', replacement: '/src' },
    ],
  },
});
