import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react-swc';
import legacy from '@vitejs/plugin-legacy';
import svgr from 'vite-plugin-svgr';
import checker from 'vite-plugin-checker';

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
  },
  resolve: {
    alias: [
      { find: '@/src', replacement: '/src' },
      { find: '@', replacement: '/src' },
    ],
  },
});
