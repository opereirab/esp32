module.exports = {
  future: {
    purgeLayersByDefault: true,
    removeDeprecatedGapUtilities: true,
  },
  purge: {
    mode: 'all',
    preserveHtmlElements: false,
    content: [
      "./src/**/*.svelte",
      "./src/**/*.html",
      "./src/**/*.js",
    ],
    options: {
      keyframes: true,
    },
  },  
  darkMode: false, // or 'media' or 'class'
  theme: {
    extend: {},
  },
  variants: {
    extend: {},
  },
  plugins: [
    require('@tailwindcss/typography'),
    require('@tailwindcss/forms'),
    require('@tailwindcss/line-clamp'),
    require('@tailwindcss/aspect-ratio')
  ],
}
