pipeline {
  agent any
  parameters {
     choice(choices: "stage\npreprod\nprod\n", description: 'Choose environment', name: 'ENV')
  }
  stages {
    stage('Build') {
      steps {
        sh 'cd C++/'
        sh 'make'
      }
    }

  }
}