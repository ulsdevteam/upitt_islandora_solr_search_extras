must edit the theme templates to print out the solr_search_links breadcrumbs


    <?php if ($solr_search_links && (count($solr_search_links)>0)): ?>
      <ul class="breadcrumbs">
      <?php foreach ($solr_search_links as $solr_search_link) : ?>
        <li class="list-item"><?php print $solr_search_link; ?></li>
      <?php endforeach; ?>
      </ul>
    <?php endif; ?>

