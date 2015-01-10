<?php

$view = new view();
$view->name = 'quizz_questions_inside';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'quiz_question_entity';
$view->human_name = 'quizz_questions_inside';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Questions';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
    'qid' => 'qid',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
    'qid' => array(
        'sortable'           => 0,
        'default_sort_order' => 'asc',
        'align'              => '',
        'separator'          => '',
        'empty_column'       => 0,
    ),
);
/* Relationship: Question: Quiz question relationship */
$handler->display->display_options['relationships']['quiz_relationship_question_qid']['id'] = 'quiz_relationship_question_qid';
$handler->display->display_options['relationships']['quiz_relationship_question_qid']['table'] = 'quiz_question_entity';
$handler->display->display_options['relationships']['quiz_relationship_question_qid']['field'] = 'quiz_relationship_question_qid';
$handler->display->display_options['relationships']['quiz_relationship_question_qid']['label'] = 'Relationship';
/* Field: Question: Label */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'quiz_question_entity';
$handler->display->display_options['fields']['title']['field'] = 'title';
/* Field: Question: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'quiz_question_entity';
$handler->display->display_options['fields']['type']['field'] = 'type';
/* Contextual filter: Quiz question relationship: Quiz_qid */
$handler->display->display_options['arguments']['quiz_qid']['id'] = 'quiz_qid';
$handler->display->display_options['arguments']['quiz_qid']['table'] = 'quiz_relationship';
$handler->display->display_options['arguments']['quiz_qid']['field'] = 'quiz_qid';
$handler->display->display_options['arguments']['quiz_qid']['relationship'] = 'quiz_relationship_question_qid';
$handler->display->display_options['arguments']['quiz_qid']['default_action'] = 'default';
$handler->display->display_options['arguments']['quiz_qid']['default_argument_type'] = 'quiz_entity';
$handler->display->display_options['arguments']['quiz_qid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['quiz_qid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['quiz_qid']['summary_options']['items_per_page'] = '25';

return $view;
