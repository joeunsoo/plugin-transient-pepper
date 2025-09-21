import js from '@eslint/js';
import globals from 'globals';
import importPlugin from 'eslint-plugin-import';
import pluginReact from 'eslint-plugin-react';
import pluginReactHooks from 'eslint-plugin-react-hooks';
import pluginPromise from 'eslint-plugin-promise';
import pluginReactRefresh from 'eslint-plugin-react-refresh';
// import prettierPluginRecommended from 'eslint-plugin-prettier/recommended';
import tseslint from 'typescript-eslint';
import { globalIgnores } from 'eslint/config';

export default tseslint.config([
  globalIgnores(['dist', 'build', '*/vite-env.d.ts']),
  {
    files: ['**/*.{js,mjs,cjs,ts,jsx,tsx}'],
    extends: [
      js.configs.recommended,
      tseslint.configs.recommended,
      pluginReactHooks.configs['recommended-latest'],
      pluginReactRefresh.configs.vite,
      importPlugin.flatConfigs.recommended, // ? https://github.com/import-js/eslint-plugin-import
      pluginPromise.configs['flat/recommended'], // ? https://github.com/eslint-community/eslint-plugin-promise
      pluginReact.configs.flat.recommended, // ? https://github.com/jsx-eslint/eslint-plugin-react
      pluginReact.configs.flat['jsx-runtime'], // ? https://github.com/jsx-eslint/eslint-plugin-react
      // prettierPluginRecommended,
    ],
    languageOptions: {
      ecmaVersion: 2020,
      globals: globals.browser,
    },
    settings: {
      react: {
        version: 'detect',
      },
      'import/resolver': {
        typescript: './tsconfig.json',
      },
    },
    plugins: {
      '@typescript-eslint': tseslint.plugin,
      // 'react-hooks': pluginReactHooks,
    },
    rules: {
      ...pluginReactHooks.configs.recommended.rules,

      'semi': ['warn', 'always'],
      'quotes': ['warn', 'single'],
      'no-multiple-empty-lines': ['warn', { 'max': 1, 'maxEOF': 0 }], // 빈줄 최대 1개
      'max-len': ['warn', { 'code': 400 }],
      'no-underscore-dangle': 'warn',
      'react/forbid-prop-types': 'warn',
      'react/jsx-no-target-blank': 'warn',
      'linebreak-style': 'warn',
      'no-param-reassign': 'warn',
      'no-use-before-define': 'warn',
      'no-nested-ternary': 'warn',
      'no-constant-condition': 'warn',
      'no-trailing-spaces': 'warn',
      'spaced-comment': 'warn', // 주석을 뒤에 쓰지 말라는 경고
      'arrow-body-style': 'warn', // 화살표 함수 안에 return을 사용할 수 있음
      'react/no-unescaped-entities': 'warn', // 문자열 내에서 " ' > } 허용
      'implicit-arrow-linebreak': 'warn', // 연산자 다음 줄 바꿈을 사용할 수 있음

      'react/prop-types': 'warn',
      'react/function-component-definition': 'warn',
      'react/jsx-no-useless-fragment': 'warn',
      'react/no-unknown-property': 'warn',
      'react/jsx-no-constructed-context-values': 'warn',

      'lines-between-class-members': 'warn',
      'promise/always-return': 'warn',

      '@typescript-eslint/no-unused-expressions': 'warn',
      '@typescript-eslint/no-var-requires': 'warn',
      '@typescript-eslint/no-explicit-any': 'warn',

      '@typescript-eslint/no-unused-vars': 'warn',
      'no-unused-vars': 'off',

      'react-hooks/rules-of-hooks': 'error',
      'react-hooks/exhaustive-deps': 'warn',
      'camelcase': [
        'warn',
        {
          properties: 'never',
          // ignoreDestructuring: true,
          // ignoreImports: true,
          // ignoreGlobals: true,
        }
      ],
      'promise/catch-or-return': 'warn',
      'consistent-return': 'warn',
      'promise/param-names': 'warn',
      'guard-for-in': 'warn',
      'array-callback-return': 'warn',

      'eqeqeq': [2, 'allow-null'], // == 금지
      'no-empty': ['error', { 'allowEmptyCatch': false }], // 빈 catch 금지
      'eol-last': 2, // 파일 끝에 개행문자가 없을 경우 경고
      'space-in-parens': [2, 'never'],// 괄호`()` 안에 공백을 추가하지 않음
      'space-before-blocks': [2, 'always'], // 블록 앞에 공백을 강제
      'brace-style': [2, '1tbs', { 'allowSingleLine': true }], // 중괄호 스타일
      'function-paren-newline': ['error', 'consistent'], // 함수의 인자가 여러줄일 경우, 첫번째 인자는 첫줄에, 나머지는 각각 한줄씩
      'object-curly-spacing': ['error', 'always'],
      'curly': 'off',
      'no-dupe-keys': 'error',
    },
  },
]);
