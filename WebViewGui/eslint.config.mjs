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
      'no-unused-vars': 'off',
      'react/react-in-jsx-scope': 'off',
      // 'react-hooks/exhaustive-deps': 'off',
      'react/display-name': 'off',
      // 'react/prop-types': 'off',
      'newline-before-return': 'warn',
      // '@typescript-eslint/no-unused-vars': 'off',
      '@typescript-eslint/no-unused-expressions': 'off',
      // 'import/order': 'warn',
      'import/no-unresolved': 'off',
      'import/no-named-as-default': 'off',

      semi: ['error', 'always'],
      quotes: ['warn', 'single'],
      'no-multiple-empty-lines': ['error', { max: 1, maxEOF: 0 }], // 빈줄 최대 1개

      'no-underscore-dangle': 'warn',
      'react/forbid-prop-types': 'warn',
      'react/jsx-filename-extension': 'off',
      'react/jsx-no-target-blank': 'warn',
      'object-curly-newline': 'off',
      'jsx-quotes': ['error', 'prefer-double'],

      'linebreak-style': 'warn',
      'no-param-reassign': 'warn',
      'max-len': ['warn', { code: 400 }],
      'no-use-before-define': 'warn',
      'no-nested-ternary': 'warn',
      'no-constant-condition': 'warn',
      'no-trailing-spaces': 'warn',
      'spaced-comment': 'warn', // 주석을 뒤에 쓰지 말라는 경고
      'arrow-body-style': 'warn', // 화살표 함수 안에 return을 사용할 수 있다.
      'react/no-unescaped-entities': 'warn', // 문자열 내에서 " ' > } 허용
      'implicit-arrow-linebreak': 'warn', // 연산자 다음 줄 바꿈을 사용할 수 있다.

      // 'react/no-array-index-key': 'warn', // key 값으로 index
      'react/prop-types': 'warn',
      'react/function-component-definition': 'warn',
      'react/jsx-no-useless-fragment': 'warn',
      'react/no-unknown-property': 'warn',
      'react/jsx-no-constructed-context-values': 'warn',
      '@typescript-eslint/no-var-requires': 'warn',
      '@typescript-eslint/no-unused-vars': 'warn',
      '@typescript-eslint/no-explicit-any': 'warn',
      'lines-between-class-members': 'warn',
      'promise/always-return': 'warn',
      'import/named': 'off',
      'react/jsx-one-expression-per-line': 'off', // 한 라인에 여러 개의 JSX를 사용할 수 있다.

      'react-hooks/rules-of-hooks': 'error',
      'react-hooks/exhaustive-deps': 'warn',
      camelcase: [
        'warn',
        {
          properties: 'never',
          // ignoreDestructuring: true,
          // ignoreImports: true,
          // ignoreGlobals: true,
        },
      ],
      'promise/catch-or-return': 'warn',
      'consistent-return': 'warn',
      'promise/param-names': 'warn',
      'guard-for-in': 'warn',
      'array-callback-return': 'warn',

      'no-shadow': 'off', // 파일 내에서 중복 이름을 사용할 수 있다.
      'operator-linebreak': 'off', // 연산자 다음 줄 바꿈을 사용할 수 있다.
      'react/jsx-props-no-spreading': 'off', // next js에서는 a에 href 없이 사용 가능
      'import/prefer-default-export': 'off', // export default 권장,
      'react/jsx-wrap-multilines': 0, // jsx에서 여러 줄에 걸쳐서 정의할 때 복잡한 rule 해제
      'react/jsx-curly-newline': 'off',
      'react/require-default-props': 'off',
      /*
      'import/extensions': [
        'error',
        'ignorePackages',
        {
          'js': 'never',
          'jsx': 'never',
          'ts': 'never',
          'tsx': 'never'
        }
      ],
      */
      'import/no-extraneous-dependencies': ['error', { devDependencies: true }],

      'no-console': 'off',
      // 'indent': ['error', 2], // 탭으로 분리(ide에서 4로 설정할 것), 데코레이터 이후의 노드는 무시
      /*
      'prettier/prettier': [
        'warn',
        {
          tabWidth: 2,
          singleQuote: true,
          bracketSameLine: true,
          trailingComma: 'all',
          semi: true,
        },
      ],
      */
      /*
      'array-element-newline': ['error', {
        'ArrayExpression': { 'multiline': true, 'minItems': 3 }, // 배열의 요소가 3개 이상일 경우, 각각 한줄씩
      }],
      */
      eqeqeq: [2, 'allow-null'], // == 금지
      'padding-line-between-statements': [
        'error',
        { blankLine: 'always', prev: '*', next: 'return' },
      ], // return 앞에는 빈줄 강제
      'no-empty': ['error', { allowEmptyCatch: false }], // 빈 catch 금지
      'eol-last': 2, // 파일 끝에 개행문자가 없을 경우 경고
      'space-in-parens': [2, 'never'], // 괄호`()` 안에 공백을 추가하지 않습니다.
      'space-before-blocks': [2, 'always'], // 블록 앞에 공백을 강제
      'brace-style': [2, '1tbs', { allowSingleLine: true }], // 중괄호 스타일
      // '@typescript-eslint/explicit-function-return-type': 2, // 명시적 함수 반환 타입 허용
      '@typescript-eslint/explicit-module-boundary-types': 0, // 명시적 모듈 바운더리 타입 허용
      'function-paren-newline': ['error', 'consistent'], // 함수의 인자가 여러줄일 경우, 첫번째 인자는 첫줄에, 나머지는 각각 한줄씩
      // 'object-property-newline': ['error', { 'allowAllPropertiesOnSameLine': false }], // 객체의 프로퍼티가 여러줄일 경우, 첫번째 프로퍼티는 첫줄에, 나머지는 각각 한줄씩
      'object-curly-spacing': ['error', 'always'],
      // 'function-call-argument-newline': ['error', 'never'], // 함수 인자에 줖바꿈 금지
      // 'comma-dangle': ['error', 'always'], // 마지막 콤마 강제, git diff 가독성 향상
    },
  },
]);
